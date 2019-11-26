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
out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

void main()
{
	// 计算顶点position
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	// 计算片段position
	FragPos = vec3(model * vec4(aPos, 1.0));
	// 计算法向量：最好不要在glsl里面写矩阵转置，太浪费性能
	Normal = mat3(transpose(inverse(model))) * aNormal;
	// 输出UV坐标
	TexCoords = aTexCoords;
};