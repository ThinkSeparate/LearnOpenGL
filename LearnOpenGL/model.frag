#version 330 core

// ���ܶ�����ɫ�͵���ɫ:�����������Ѿ������ˣ���Ϊ����ĵƽṹ��Ͳ��ʽṹ��ȡ��������
uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 viewPos;

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

struct Material {
	sampler2D diffuse;	// ��������ͼ
	sampler2D specular;	// ���淴����ͼ
	float shininess;	// �����
};

uniform Material material;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

// out�������ֵ�������ݸ���һ����Ⱦ�����ֵ
out vec4 FragColor;

void main()
{
	// ����theta����Ƭ�κ͹�Ȧ�ļн�
	vec3 lightDir = normalize(light.position - FragPos);
	float theta = dot(lightDir, normalize(-light.direction));

	// ����ϵ��
	float epsilon   = light.innerCutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);    
	 
	// ����������
		vec3 norm = normalize(Normal);
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

		float distance = length(light.position - FragPos);
		float attennation = 1.0f / (light.constant + light.linear * distance + 
				light.quadratic * (distance * distance));
		vec3 result = attennation * (ambient + diffuse * intensity + specular * intensity);

		FragColor = vec4(result, 1.0f);
	
};