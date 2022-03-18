#version 330

in vec2 vTexCoord;

out vec4 outColor;

uniform sampler2D uTexture;

void main()
{
    outColor = texture(uTexture, vTexCoord);
    // outColor = vec4(0.0, 0.0, 1.0, 1.0);
}