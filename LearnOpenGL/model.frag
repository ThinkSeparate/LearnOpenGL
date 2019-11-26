#version 330 core

// 接受对象颜色和灯颜色:这两个变量已经废弃了，因为后面的灯结构体和材质结构体取代了他们
uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 viewPos;

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

struct Material {
	sampler2D diffuse;	// 漫反射贴图
	sampler2D specular;	// 镜面反射贴图
	float shininess;	// 反光度
};

uniform Material material;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

// out定义输出值，即传递给下一个渲染步骤的值
out vec4 FragColor;

void main()
{
	// 计算theta，即片段和光圈的夹角
	vec3 lightDir = normalize(light.position - FragPos);
	float theta = dot(lightDir, normalize(-light.direction));

	// 计算系数
	float epsilon   = light.innerCutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);    
	 
	// 计算漫反射
		vec3 norm = normalize(Normal);
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

		float distance = length(light.position - FragPos);
		float attennation = 1.0f / (light.constant + light.linear * distance + 
				light.quadratic * (distance * distance));
		vec3 result = attennation * (ambient + diffuse * intensity + specular * intensity);

		FragColor = vec4(result, 1.0f);
	
};