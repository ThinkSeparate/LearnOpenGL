#version 330 core
// 顶点值
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

// 程序输入值
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// 输出值
out vec2 TexCoords;

void main()
{
	// 计算顶点position
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	// 输出UV坐标
	TexCoords = aTexCoords;
};