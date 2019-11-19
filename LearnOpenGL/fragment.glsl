#version 330 core
// out�������ֵ�������ݸ���һ����Ⱦ�����ֵ
out vec4 FragColor;

// ���ܶ�����ɫ�͵���ɫ
uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 lightPos;

in vec3 FragPos;
in vec3 Normal;

void main()
{
	// ��׼��������
	vec3 norm = normalize(Normal);

	// ������շ���
	vec3 lightDir = normalize(lightPos - FragPos);

	// ����������
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	// ���뻷����������
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;

	vec3 result = (ambient + diffuse) * objectColor;

	FragColor = vec4(result, 1.0f);
};