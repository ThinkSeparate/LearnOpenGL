// ʹ��OpenGL3.3�汾��ģʽ�Ǻ�����Ⱦģʽ
#version 330 core
// in�����������ԣ���ͨ�������߼����ݸ�GPU��layout (location = 0)�����ڴ�����ֵ��ʱ��λ���Ե�λ��
// vec3��vector��������3��Ԫ��
layout (location = 0) in vec3 aPos;
// ����һ��λ��Ϊ1����ɫ����
layout (location = 1) in vec3 aColor;

// ��Ƭ����ɫ�����һ����ɫ
out vec3 ourColor;

// mian��������ɫ���������ں���
void main()
{
	// ������ɫ����������ݱ�����gl_Position�����ֵ��������Ⱦ����һ����
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	ourColor = aColor;
};