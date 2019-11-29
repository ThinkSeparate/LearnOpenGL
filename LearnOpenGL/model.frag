#version 330 core

uniform sampler2D texture1;

in vec2 TexCoords;

// out�������ֵ�������ݸ���һ����Ⱦ�����ֵ
out vec4 FragColor;

void main()
{
	vec4 texColor = texture(texture1, TexCoords);
	if (texColor.a < 0.1f) {
		// ��������֤Ƭ�β��ᱻ��һ��������͸��Ƭ�β���ʾ��
		discard;
	}
    FragColor = texColor;
};