#version 330 core
// out�������ֵ�������ݸ���һ����Ⱦ�����ֵ
out vec4 FragColor;

// ���ܶ�����ɫ�͵���ɫ
uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

struct Material {
	vec3 ambient;	// ������
	vec3 diffuse;	// ������
	vec3 specular;	// ���淴��
	float shininess;	// �����
};

uniform Material material;

in vec3 FragPos;
in vec3 Normal;

void main()
{
	// ���㻷����
	vec3 ambient = lightColor * material.ambient;

	// ����������
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = lightColor * (diff * material.diffuse);

	// ���㾵���
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPos - FragPos);
	// reflect�������ӹ�Դָ��Ƭ�ε���������������
	vec3 reflectDir = reflect(-lightDir, norm);
	// ���㾵�����
	// pow���������㷴��ȣ������Խ�ߣ���������Խǿ��ɢ��Խ�٣��߹���ԽС
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = lightColor * (spec * material.specular);

	vec3 result = ambient + diffuse + specular;

	FragColor = vec4(result, 1.0f);
};