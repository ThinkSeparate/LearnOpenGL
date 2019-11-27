#version 330 core

uniform vec3 viewPos;

struct Material {
	sampler2D diffuse;	// 漫反射贴图
	sampler2D specular;	// 镜面反射贴图
	float shininess;	// 反光度
};

uniform Material material;

struct DirLight {
	// 物理信息
	vec3 direction;

	// 照射属性
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirLight dirLight;

struct PointLight {
	// 物理信息
	vec3 position;

	// 照射属性
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	//光衰减
	float constant;
	float linear;
	float quadratic;
};
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

struct SpotLight {
	// 物理信息
	vec3 position;
	vec3 direction;

	// 光圈
	float innerCutOff;
	float outerCutOff;

	// 照射属性
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	// 光衰减
	float constant;
	float linear;
	float quadratic;
};

uniform SpotLight spotLight;

struct Light {
	vec3 position;	// 这四个变量用于处理灯的物理信息
	vec3 direction;
	float innerCutOff;	// 内外圆锥实现光圈的边缘平滑
	float outerCutOff;

    vec3 ambient;	// 这三个变量用于处理灯的照射属性
    vec3 diffuse;
    vec3 specular;

	float constant;	// 这三个值用于光衰减计算
	float linear;
	float quadratic;
};

uniform Light light;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

// out定义输出值，即传递给下一个渲染步骤的值
out vec4 FragColor;

// 定义函数
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	// 定义输出颜色值
	vec3 output;

	// 计算法向量
	vec3 norm = normalize(Normal);
	// 计算观察方向
	vec3 viewDir = normalize(viewPos - FragPos);

	// 加入定向光
	output += CalcDirLight(dirLight, norm, viewDir);

	for (int i = 0; i < NR_POINT_LIGHTS; i++) {
		output += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
	}

	// 加入聚光
	output += CalcSpotLight(spotLight, norm, FragPos, viewDir);

	// 输出结果
	FragColor = vec4(output, 1.0f);
};

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
	// 计算漫反射
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoords)));

	// 计算环境光
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	// 计算镜面光
	float specularStrength = 0.5f;
	// reflect函数（从光源指向片段的向量，法向量）
	vec3 reflectDir = reflect(-lightDir, normal);
	// 计算镜面分量
	// pow函数，计算反光度，反光度越高，反光能力越强，散射越少，高光点就越小
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * (spec * vec3(texture(material.specular, TexCoords)));

	return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	// 计算theta，即片段和光圈的夹角
	vec3 lightDir = normalize(light.position - FragPos); 
	 
	// 计算漫反射
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoords)));

	// 计算环境光
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	// 计算镜面光
	float specularStrength = 0.5f;
	// reflect函数（从光源指向片段的向量，法向量）
	vec3 reflectDir = reflect(-lightDir, normal);
	// 计算镜面分量
	// pow函数，计算反光度，反光度越高，反光能力越强，散射越少，高光点就越小
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * (spec * vec3(texture(material.specular, TexCoords)));

	float distance = length(light.position - FragPos);
	float attennation = 1.0f / (light.constant + light.linear * distance + 
			light.quadratic * (distance * distance));
	return attennation * (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {

	// 计算theta，即片段和光圈的夹角
	vec3 lightDir = normalize(light.position - FragPos);
	float theta = dot(lightDir, normalize(-light.direction));

	// 计算系数
	float epsilon   = light.innerCutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);    
	 
	// 计算漫反射
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoords)));

	// 计算环境光
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	// 计算镜面光
	float specularStrength = 0.5f;
	vec3 reflectDir = reflect(-lightDir, normal);
	// 计算镜面分量
	// pow函数，计算反光度，反光度越高，反光能力越强，散射越少，高光点就越小
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * (spec * vec3(texture(material.specular, TexCoords)));

	float distance = length(light.position - fragPos);
	float attennation = 1.0f / (light.constant + light.linear * distance + 
			light.quadratic * (distance * distance));
	return attennation * (ambient + diffuse * intensity + specular * intensity);
}