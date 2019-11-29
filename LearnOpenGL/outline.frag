#version 330 core

uniform sampler2D texture1;

// out定义输出值，即传递给下一个渲染步骤的值
out vec4 FragColor;

void main()
{
    FragColor = vec4(0.04, 0.28, 0.26, 1.0);
};