#version 330 core

uniform sampler2D texture1;

in vec2 TexCoords;

// out定义输出值，即传递给下一个渲染步骤的值
out vec4 FragColor;

void main()
{
    FragColor = texture(texture1, TexCoords);
};