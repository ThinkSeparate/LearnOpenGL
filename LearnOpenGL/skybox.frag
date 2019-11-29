#version 330 core

uniform samplerCube cubemap;

in vec3 TexCoords;

// out�������ֵ�������ݸ���һ����Ⱦ�����ֵ
out vec4 FragColor;

void main()
{
    FragColor = texture(cubemap, TexCoords);
};