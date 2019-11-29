#version 330 core
// 顶点值
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

// 输出值
out vec2 TexCoords;

void main()
{
	// 计算顶点position
	gl_Position = vec4(aPos.x, aPos.y, 0.0f, 1.0f);
	// 输出UV坐标
	TexCoords = aTexCoords;
};