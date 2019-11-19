// 使用OpenGL3.3版本，模式是核心渲染模式
#version 330 core
// in声明输入属性，即通过程序逻辑传递给GPU；layout (location = 0)用于在传递数值的时候定位属性的位置
// vec3是vector变量，有3个元素
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// mian函数是着色器程序的入口函数
void main()
{
	// 顶点着色器的输出内容必须有gl_Position；这个值将用于渲染的下一步骤
	// gl_Position应该为标准化设备坐标（-1，1），超出此范围的顶点将会被舍弃
	// 矩阵乘法从右向左读
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
};