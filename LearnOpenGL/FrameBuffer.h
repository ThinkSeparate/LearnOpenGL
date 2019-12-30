#pragma once

#include <glad/glad.h>	// 用来管理OpenGL函数指针
#include <GLFW/glfw3.h>	// glfw3，包含了OpenGL的库使用

#include <iostream>
using namespace std;

// OpenGL帧缓冲类型
enum FRAME_BUFFER_TYPE
{
	READ_ADN_DRAW,
	READ,
	DRAW,
};

// TODO: 深度缓冲和模板缓冲需要区别需要创建，暂时不写了
class FrameBuffer
{
public:
	// 深度和模板默认设置为false
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
	// 如果你不需要从一个缓冲中采样数据，那么对这个缓冲使用渲染缓冲对象会是明智的选择。如果你需要从缓冲中采样颜色或深度值等数据，那么你应该选择纹理附件
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

