// ʹ��OpenGL3.3�汾��ģʽ�Ǻ�����Ⱦģʽ
#version 330 core
// in�����������ԣ���ͨ�������߼����ݸ�GPU��layout (location = 0)�����ڴ�����ֵ��ʱ��λ���Ե�λ��
// vec3��vector��������3��Ԫ��
layout (location = 0) in vec3 aPos;
// ����һ��λ��Ϊ1����ɫ����
layout (location = 1) in vec3 aColor;
// ����һ��λ��Ϊ2����ͼ����
layout (location = 2) in vec2 aTexCoord;

// ��Ƭ����ɫ�����һ����ɫ
out vec3 ourColor;
// ��Ƭ����ɫ�����һ����ͼ����
out vec2 TexCoord;

uniform mat4 transform;

// mian��������ɫ���������ں���
void main()
{
	// ������ɫ����������ݱ�����gl_Position�����ֵ��������Ⱦ����һ����
	gl_Position = transform * vec4(aPos, 1.0f);
	ourColor = aColor;
	TexCoord = aTexCoord;
};