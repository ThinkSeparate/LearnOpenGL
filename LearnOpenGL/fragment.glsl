#version 330 core
// out定义输出值，即传递给下一个渲染步骤的值
out vec4 FragColor;

// 接受对象颜色和灯颜色
uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

struct Light {
	//vec3 position; // 使用定向光就不再需要了
	vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

struct Material {
	sampler2D diffuse;	// 漫反射贴图
	sampler2D specular;	// 镜面反射贴图
	float shininess;	// 反光度
};

uniform Material material;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

void main()
{
	// 计算漫反射
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoords)));

	// 计算环境光
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	// 计算镜面光
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPos - FragPos);
	// reflect函数（从光源指向片段的向量，法向量）
	vec3 reflectDir = reflect(-lightDir, norm);
	// 计算镜面分量
	// pow函数，计算反光度，反光度越高，反光能力越强，散射越少，高光点就越小
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * (spec * vec3(texture(material.specular, TexCoords)));

	vec3 result = ambient + diffuse + specular;

	FragColor = vec4(result, 1.0f);
};