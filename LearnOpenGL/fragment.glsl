#version 330 core
// out定义输出值，即传递给下一个渲染步骤的值
out vec4 FragColor;

// 接受对象颜色和灯颜色
uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 FragPos;
in vec3 Normal;

void main()
{
	// 标准化法向量
	vec3 norm = normalize(Normal);

	// 计算光照方向
	vec3 lightDir = normalize(lightPos - FragPos);

	// 计算漫反射
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	// 加入环境光照因子
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;

	// 加入高光
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPos - FragPos);
	// reflect函数（从光源指向片段的向量，法向量）
	vec3 reflectDir = reflect(-lightDir, norm);
	// 计算镜面分量
	// pow函数，计算反光度，反光度越高，反光能力越强，散射越少，高光点就越小
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor;

	FragColor = vec4(result, 1.0f);
};