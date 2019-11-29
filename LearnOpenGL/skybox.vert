#version 330 core
// 顶点值
layout (location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 view;

// 输出值
out vec3 TexCoords;

void main()
{
	// 计算顶点position
	gl_Position = projection * view * vec4(aPos, 1.0);
	// 输出UV坐标
	TexCoords = aPos;
};