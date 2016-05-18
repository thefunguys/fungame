uniform sampler2D texture;
uniform float flicker;
uniform vec2 dxy;

void main()
{
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    float pdist = sqrt(dxy.x * dxy.x + dxy.y * dxy.y);
    float l = flicker * 50.0 / (pdist + 100.0);
    gl_FragColor = gl_Color * pixel * vec4(l, l, l, 1.0);
}
