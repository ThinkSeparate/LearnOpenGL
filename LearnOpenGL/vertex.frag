#version 330 core

uniform sampler2D texture1;

in vec2 TexCoords;
in vec3 Position;
in vec3 Normal;

// out�������ֵ�������ݸ���һ����Ⱦ�����ֵ
out vec4 FragColor;

void main()
{
    FragColor = texture(texture1, TexCoords);
};