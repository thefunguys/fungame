#version 130
uniform sampler2D texture;
uniform vec2 windowsize;
uniform float flicker;

void main()
{
    // gl_FragCoord depends on the window size, so we normalize it
    vec2 wp = gl_FragCoord.xy * vec2(640.0, 480.0) / windowsize;
    vec2 wc = vec2(640.0, 480.0) / vec2(2.0, 2.0);
    // janky -- assumes player/light source is always at ccenter of window
    float dist2 = (wc.x - wp.x) * (wc.x - wp.x) + (wc.y - wp.y) * (wc.y - wp.y);
    float dampen = 2000.0 / (dist2 + 2000.0);
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    vec4 light = vec4(dampen, dampen, dampen, 1.0);
    gl_FragColor = gl_Color * pixel * light * vec4(flicker, flicker, flicker, 1.0);
}
