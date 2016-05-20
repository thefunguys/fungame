#version 130
uniform sampler2D texture;
uniform sampler2D smap;
uniform vec2 windowsize;
uniform float flicker;

void main()
{
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    vec4 light = texture2D(smap, gl_FragCoord.xy / windowsize);
    gl_FragColor = gl_Color * pixel * light * vec4(flicker, flicker, flicker, 1.0);
}
