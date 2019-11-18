#version 330 core
// out�������ֵ�������ݸ���һ����Ⱦ�����ֵ
out vec4 FragColor;

// ���ܶ�����ɫ��������
in vec3 ourColor;
in vec2 TexCoord;

// ����һ����������,sampler2D��2d��������
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
	// OpenGL��rgbaֵΪfloat���ͣ���ֵ��0-1֮��
	// glsl�ı���֧����ϣ�����ʹ�õȲ���
	// texture���������ݸ������������ͼ���꣬�����Ƭ����ɫ������ɫ
	// mix�����������������һ���ı�����ϣ�������ֵ��ʾ�ڶ���ͼƬ�ڻ����ռ�ı���
	FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2);
};