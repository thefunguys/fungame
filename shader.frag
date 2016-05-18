#version 130
uniform sampler2D texture;
uniform float flicker;
uniform vec2 dxy;
uniform vec2 wh;

void main()
{
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    float dx = dxy.x - gl_TexCoord[0].x * wh.x;
    float dy = dxy.y - gl_TexCoord[0].y * wh.y;
    float pdist = sqrt(dx * dx + dy * dy);
//    float l = flicker * (1.0 + -1.0 * pdist * pdist * 0.0001);
    float l = flicker * 200.0 / (pdist * pdist + 200.0);
    gl_FragColor = gl_Color * pixel * vec4(l, l, l, 1.0);
}
