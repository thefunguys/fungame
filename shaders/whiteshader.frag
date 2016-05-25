#version 130
uniform sampler2D texture;

void main()
{
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    gl_FragColor = step(vec4(0.01, 0.01, 0.01, 1.0), pixel);
}
