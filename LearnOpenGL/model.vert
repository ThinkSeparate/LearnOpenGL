#version 330 core
// ����ֵ
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

// ��������ֵ
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out VS_OUT {
	// ���ֵ
	vec2 TexCoords;
	vec3 Normal;
	vec3 Position;
} vs_out;

void main()
{
	// ���㶥��position
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	// ���UV����
	vs_out.TexCoords = aTexCoords;
	vs_out.Normal = mat3(transpose(inverse(model))) * aNormal;
    vs_out.Position = vec3(model * vec4(aPos, 1.0));
};