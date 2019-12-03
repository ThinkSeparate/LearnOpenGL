#version 330 core

uniform sampler2D texture1;

in vec2 TexCoords;
in vec3 Position;
in vec3 Normal;

// out定义输出值，即传递给下一个渲染步骤的值
out vec4 FragColor;

void main()
{
    FragColor = texture(texture1, TexCoords);
};