#version 330 core
// out�������ֵ�������ݸ���һ����Ⱦ�����ֵ
out vec4 FragColor;

// ���ܶ�����ɫ�͵���ɫ
uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

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

	// ����߹�
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPos - FragPos);
	// reflect�������ӹ�Դָ��Ƭ�ε���������������
	vec3 reflectDir = reflect(-lightDir, norm);
	// ���㾵�����
	// pow���������㷴��ȣ������Խ�ߣ���������Խǿ��ɢ��Խ�٣��߹���ԽС
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor;

	FragColor = vec4(result, 1.0f);
};