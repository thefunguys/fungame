#version 130
uniform sampler2D texture;

vec4 sample_tex(vec2 pt)
{
    return texture2D(texture, pt);
}

void main()
{
    // sample some points around here
    float sampleoff = 0;
    int i, j;
    vec4 sampled;
    int its = 0;
    for (i = -1; i <= 1; i++) {
        for (j = -1; j < 1; j++) {
            sampled += sample_tex(gl_TexCoord[0].xy + vec2(i*sampleoff, j*sampleoff));
            its++;
        }
    }

    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    gl_FragColor = gl_Color * (sampled / its); 

}
