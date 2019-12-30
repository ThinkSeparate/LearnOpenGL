#pragma once

#include <glad/glad.h>	// ��������OpenGL����ָ��
#include <GLFW/glfw3.h>	// glfw3��������OpenGL�Ŀ�ʹ��

#include <iostream>
using namespace std;

// OpenGL֡��������
enum FRAME_BUFFER_TYPE
{
	READ_ADN_DRAW,
	READ,
	DRAW,
};

// TODO: ��Ȼ����ģ�建����Ҫ������Ҫ��������ʱ��д��
class FrameBuffer
{
public:
	// ��Ⱥ�ģ��Ĭ������Ϊfalse
	FrameBuffer(FRAME_BUFFER_TYPE type, int width, int height, bool colorBuffer, bool depthBuffer = false, bool stencilBuffer = false, bool mass = false, int smaples = 0);
	void Bind();
	void Unbind();
	unsigned int getTexture();
private:
	FRAME_BUFFER_TYPE type;
	int width;
	int height;
	bool colorBuffer;
	bool depthBuffer;
	bool stencilBuffer;
	bool mass;
	int samples;
	unsigned int frameBuffer;
	unsigned int multiFrameBuffer;
	unsigned int colorTexture;
	unsigned int multiColorTexture;
	// ����㲻��Ҫ��һ�������в������ݣ���ô���������ʹ����Ⱦ�������������ǵ�ѡ���������Ҫ�ӻ����в�����ɫ�����ֵ�����ݣ���ô��Ӧ��ѡ��������
	unsigned int renderBufferObject;
	unsigned int multiRenderBufferObject;
	void createFrameBuffer();
	void createMultiFrameBuffer();
	void attachColorBuffer();
	void attachMultiColorBuffer();
	void attachDepthBuffer();
	void attachStencilBuffer();
	void attachRenderBufferObject();
	void attachMultiRenderBufferObject();
};

