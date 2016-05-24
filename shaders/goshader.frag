#version 130
uniform sampler2D texture;
uniform vec2 windowsize;
uniform float flicker;
uniform vec2 direction;
uniform vec3 highlight;

void main()
{

    // gl_FragCoord depends on the window size, so we normalize it
    int offset = 0;
    float lightd_off = 10000.0;
    float lightb_off = 100000.0;
    float dark_off = 500.0;
    vec2 wp = gl_FragCoord.xy * vec2(640.0, 480.0) / windowsize;
    vec2 wc = vec2(640.0, 480.0) / vec2(2.0, 2.0);
    // janky -- assumes player/light source is always at ccenter of window
    vec2 pix_dir = wp - wc;
    float dist2 = pix_dir.x * pix_dir.x + pix_dir.y * pix_dir.y;
    float xdoty = direction.x * pix_dir.x + direction.y * pix_dir.y;
    float lr_dim = dist2 * 0.75 * (direction.x*direction.x + direction.y*direction.y);
    float lr_bright = dist2 * 0.9924 * (direction.x*direction.x + direction.y*direction.y);;
    float dampen = 0.;
    if( xdoty*xdoty >= lr_bright && xdoty > 0) {
    	dampen = lightb_off / (dist2 + lightb_off);
    } else if(xdoty*xdoty >= lr_dim && xdoty > 0) {
    	dampen = lightd_off / (dist2 + lightd_off);
    } else {
        dampen = dark_off / (dist2 + dark_off);
    }
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    vec4 light = vec4(dampen, dampen, dampen, 1.0);
    gl_FragColor = gl_Color * pixel * light * vec4(highlight, 1.0);

}



