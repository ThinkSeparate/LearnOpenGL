// ʹ��OpenGL3.3�汾��ģʽ�Ǻ�����Ⱦģʽ
#version 330 core
// in�����������ԣ���ͨ�������߼����ݸ�GPU��layout (location = 0)�����ڴ�����ֵ��ʱ��λ���Ե�λ��
// vec3��vector��������3��Ԫ��
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// mian��������ɫ���������ں���
void main()
{
	// ������ɫ����������ݱ�����gl_Position�����ֵ��������Ⱦ����һ����
	// gl_PositionӦ��Ϊ��׼���豸���꣨-1��1���������˷�Χ�Ķ��㽫�ᱻ����
	// ����˷����������
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
};