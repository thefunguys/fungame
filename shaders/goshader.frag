#version 130
uniform sampler2D texture;
uniform vec2 windowsize;
uniform float flicker;
uniform vec2 direction;
uniform vec3 highlight;

void main()
{

    int offset = 0;
    float lightd_off = 0.01;
    float lightb_off = 0.01;
    float dark_off = 0.006;
    // gl_FragCoord depends on the window size, so we normalize it
    vec2 wp = gl_FragCoord.xy  / windowsize;
    // lightsource
    // vec2 wc = vec2(640.0, 480.0) / vec2(2.0, 2.0);
    vec2 wc = vec2(0.5, 0.5);
    // janky -- assumes player/light source is always at ccenter of window
    vec2 pix_dir = wp - wc;
    float dist2 = dot(pix_dir, pix_dir);
    float xdoty = dot(direction, pix_dir);
    float dir2 = dot(direction, direction);
    float lr_dim = dist2 * 0.75 * dir2;
    float lr_bright = dist2 * 0.9924 * dir2;
    float dampen = 0.;
    bool colored = false;
    /*if( xdoty*xdoty >= lr_bright && xdoty > 0) {
    	dampen = lightb_off / (dist2 + lightb_off);
    } else*/ if(xdoty*xdoty >= lr_dim && xdoty > 0) {
    	dampen = flicker * lightd_off / (dist2 + lightd_off);
        colored = true;
    } else {
        dampen = flicker * dark_off / (dist2 + dark_off);
    }
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    // a la http://www.pouet.net/topic.php?which=5167
    float gray = dot(pixel.rgb, vec3(0.299, 0.587, 0.114));
    vec4 pix;
    colored ? pix = pixel : pix = vec4(gray, gray, gray, pixel.a);
    vec4 light = vec4(dampen, dampen, dampen, 1.0);
    gl_FragColor = gl_Color * pix * light * vec4(highlight, 1.0);

}
