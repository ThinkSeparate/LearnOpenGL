#version 330 core
// out�������ֵ�������ݸ���һ����Ⱦ�����ֵ
out vec4 FragColor;

// ���ܶ�����ɫ��������
in vec3 ourColor;

void main()
{
	// OpenGL��rgbaֵΪfloat���ͣ���ֵ��0-1֮��
	// glsl�ı���֧����ϣ�����ʹ�õȲ���
	FragColor = vec4(ourColor, 1.0);
};