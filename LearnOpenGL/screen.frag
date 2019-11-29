#version 330 core

uniform sampler2D screenTexture;

in vec2 TexCoords;

// out定义输出值，即传递给下一个渲染步骤的值
out vec4 FragColor;

void main()
{
    FragColor = texture(screenTexture, TexCoords);
};