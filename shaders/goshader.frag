#version 130
uniform sampler2D texture;
uniform vec2 windowsize;
uniform float flicker;

void main()
{
    // gl_FragCoord depends on the window size, so we normalize it
    vec2 wp = gl_FragCoord.xy * vec2(640.0, 480.0) / windowsize;
    // janky -- assumes player/light source is always at ccenter of window
    float dist2 = (320.0 - wp.x) * (320.0 - wp.x) + (240.0 - wp.y) * (240.0 - wp.y);
    float dampen = 1000.0 / (dist2 + 1000.0);
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    vec4 light = vec4(dampen, dampen, dampen, 1.0);
    gl_FragColor = gl_Color * pixel * light * vec4(flicker, flicker, flicker, 1.0);
}
