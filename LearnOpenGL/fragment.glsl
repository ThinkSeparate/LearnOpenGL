#version 330 core
// out�������ֵ�������ݸ���һ����Ⱦ�����ֵ
out vec4 FragColor;

// ���ܶ�����ɫ�͵���ɫ
uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

struct Light {
	//vec3 position; // ʹ�ö����Ͳ�����Ҫ��
	vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

struct Material {
	sampler2D diffuse;	// ��������ͼ
	sampler2D specular;	// ���淴����ͼ
	float shininess;	// �����
};

uniform Material material;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

void main()
{
	// ����������
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoords)));

	// ���㻷����
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	// ���㾵���
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPos - FragPos);
	// reflect�������ӹ�Դָ��Ƭ�ε���������������
	vec3 reflectDir = reflect(-lightDir, norm);
	// ���㾵�����
	// pow���������㷴��ȣ������Խ�ߣ���������Խǿ��ɢ��Խ�٣��߹���ԽС
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * (spec * vec3(texture(material.specular, TexCoords)));

	vec3 result = ambient + diffuse + specular;

	FragColor = vec4(result, 1.0f);
};