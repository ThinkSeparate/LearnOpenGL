#version 330 core
// out定义输出值，即传递给下一个渲染步骤的值
out vec4 FragColor;

// 接受顶点着色器的输入
in vec3 ourColor;

void main()
{
	// OpenGL的rgba值为float类型，数值在0-1之间
	// glsl的变量支持组合，分量使用等操作
	FragColor = vec4(ourColor, 1.0);
};