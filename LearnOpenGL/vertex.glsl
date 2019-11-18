// 使用OpenGL3.3版本，模式是核心渲染模式
#version 330 core
// in声明输入属性，即通过程序逻辑传递给GPU；layout (location = 0)用于在传递数值的时候定位属性的位置
// vec3是vector变量，有3个元素
layout (location = 0) in vec3 aPos;
// 声明一个位置为1的颜色输入
layout (location = 1) in vec3 aColor;
// 声明一个位置为2的贴图坐标
layout (location = 2) in vec2 aTexCoord;

// 向片段着色器输出一个颜色
out vec3 ourColor;
// 向片段着色器输出一个贴图坐标
out vec2 TexCoord;

uniform mat4 transform;

// mian函数是着色器程序的入口函数
void main()
{
	// 顶点着色器的输出内容必须有gl_Position；这个值将用于渲染的下一步骤
	gl_Position = transform * vec4(aPos, 1.0f);
	ourColor = aColor;
	TexCoord = aTexCoord;
};