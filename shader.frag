#version 130
uniform sampler2D texture;
uniform sampler2D smap;
uniform vec2 windowsize;
uniform float flicker;

void main()
{
    vec2 wp = gl_FragCoord.xy * vec2(640.0, 480.0) / windowsize;
    float dist2 = (320.0 - wp.x) * (320.0 - wp.x) + (240.0 - wp.y) * (240.0 - wp.y);
    float dampen = 1000.0 / (dist2 + 1000.0);
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    // vec4 light = texture2D(smap, gl_FragCoord.xy / windowsize);
    vec4 light = vec4(dampen, dampen, dampen, 1.0);
    gl_FragColor = gl_Color * pixel * light * vec4(flicker, flicker, flicker, 1.0);
}
