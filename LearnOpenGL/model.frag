#version 330 core

uniform sampler2D texture1;

uniform vec3 cameraPos;
uniform samplerCube skybox;

in vec2 TexCoords;
in vec3 Position;
in vec3 Normal;

// out定义输出值，即传递给下一个渲染步骤的值
out vec4 FragColor;

void main()
{
	float ratio = 1.00 / 1.52;
	vec3 I = normalize(Position - cameraPos);
	vec3 R = refract(I, normalize(Normal), ratio);
    FragColor = vec4(texture(skybox, R).rgb, 1.0);
};