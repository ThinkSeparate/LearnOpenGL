#version 330 core
// out定义输出值，即传递给下一个渲染步骤的值
out vec4 FragColor;

// 接受对象颜色和灯颜色
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	FragColor = vec4(objectColor * lightColor, 1.0f);
};