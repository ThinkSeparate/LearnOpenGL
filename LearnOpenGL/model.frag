#version 330 core

uniform vec3 viewPos;

struct Material {
	sampler2D diffuse;	// ��������ͼ
	sampler2D specular;	// ���淴����ͼ
	float shininess;	// �����
};

uniform Material material;

struct DirLight {
	// ������Ϣ
	vec3 direction;

	// ��������
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirLight dirLight;

struct PointLight {
	// ������Ϣ
	vec3 position;

	// ��������
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	//��˥��
	float constant;
	float linear;
	float quadratic;
};
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

struct SpotLight {
	// ������Ϣ
	vec3 position;
	vec3 direction;

	// ��Ȧ
	float innerCutOff;
	float outerCutOff;

	// ��������
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	// ��˥��
	float constant;
	float linear;
	float quadratic;
};

uniform SpotLight spotLight;

struct Light {
	vec3 position;	// ���ĸ��������ڴ���Ƶ�������Ϣ
	vec3 direction;
	float innerCutOff;	// ����Բ׶ʵ�ֹ�Ȧ�ı�Եƽ��
	float outerCutOff;

    vec3 ambient;	// �������������ڴ���Ƶ���������
    vec3 diffuse;
    vec3 specular;

	float constant;	// ������ֵ���ڹ�˥������
	float linear;
	float quadratic;
};

uniform Light light;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

// out�������ֵ�������ݸ���һ����Ⱦ�����ֵ
out vec4 FragColor;

// ���庯��
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	// ���������ɫֵ
	vec3 output;

	// ���㷨����
	vec3 norm = normalize(Normal);
	// ����۲췽��
	vec3 viewDir = normalize(viewPos - FragPos);

	// ���붨���
	output += CalcDirLight(dirLight, norm, viewDir);

	for (int i = 0; i < NR_POINT_LIGHTS; i++) {
		output += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
	}

	// ����۹�
	output += CalcSpotLight(spotLight, norm, FragPos, viewDir);

	// ������
	FragColor = vec4(output, 1.0f);
};

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
	// ����������
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoords)));

	// ���㻷����
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	// ���㾵���
	float specularStrength = 0.5f;
	// reflect�������ӹ�Դָ��Ƭ�ε���������������
	vec3 reflectDir = reflect(-lightDir, normal);
	// ���㾵�����
	// pow���������㷴��ȣ������Խ�ߣ���������Խǿ��ɢ��Խ�٣��߹���ԽС
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * (spec * vec3(texture(material.specular, TexCoords)));

	return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	// ����theta����Ƭ�κ͹�Ȧ�ļн�
	vec3 lightDir = normalize(light.position - FragPos); 
	 
	// ����������
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoords)));

	// ���㻷����
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	// ���㾵���
	float specularStrength = 0.5f;
	// reflect�������ӹ�Դָ��Ƭ�ε���������������
	vec3 reflectDir = reflect(-lightDir, normal);
	// ���㾵�����
	// pow���������㷴��ȣ������Խ�ߣ���������Խǿ��ɢ��Խ�٣��߹���ԽС
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * (spec * vec3(texture(material.specular, TexCoords)));

	float distance = length(light.position - FragPos);
	float attennation = 1.0f / (light.constant + light.linear * distance + 
			light.quadratic * (distance * distance));
	return attennation * (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {

	// ����theta����Ƭ�κ͹�Ȧ�ļн�
	vec3 lightDir = normalize(light.position - FragPos);
	float theta = dot(lightDir, normalize(-light.direction));

	// ����ϵ��
	float epsilon   = light.innerCutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);    
	 
	// ����������
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoords)));

	// ���㻷����
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	// ���㾵���
	float specularStrength = 0.5f;
	vec3 reflectDir = reflect(-lightDir, normal);
	// ���㾵�����
	// pow���������㷴��ȣ������Խ�ߣ���������Խǿ��ɢ��Խ�٣��߹���ԽС
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * (spec * vec3(texture(material.specular, TexCoords)));

	float distance = length(light.position - fragPos);
	float attennation = 1.0f / (light.constant + light.linear * distance + 
			light.quadratic * (distance * distance));
	return attennation * (ambient + diffuse * intensity + specular * intensity);
}