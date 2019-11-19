#version 330 core
// out定义输出值，即传递给下一个渲染步骤的值
out vec4 FragColor;

// 接受对象颜色和灯颜色
uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 lightPos;

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

	vec3 result = (ambient + diffuse) * objectColor;

	FragColor = vec4(result, 1.0f);
};