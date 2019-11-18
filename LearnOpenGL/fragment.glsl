#version 330 core
// out�������ֵ�������ݸ���һ����Ⱦ�����ֵ
out vec4 FragColor;

// ���ܶ�����ɫ��������
in vec3 ourColor;
in vec2 TexCoord;

// ����һ����������,sampler2D��2d��������
uniform sampler2D ourTexture;

void main()
{
	// OpenGL��rgbaֵΪfloat���ͣ���ֵ��0-1֮��
	// glsl�ı���֧����ϣ�����ʹ�õȲ���
	FragColor = texture(ourTexture, TexCoord);
};