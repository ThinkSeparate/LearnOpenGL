#version 330 core

uniform sampler2D texture1;

in vec2 TexCoords;

// out�������ֵ�������ݸ���һ����Ⱦ�����ֵ
out vec4 FragColor;

void main()
{
	// ������
	FragColor = vec4(vec3(gl_FragCoord.z), 1.0f);
};