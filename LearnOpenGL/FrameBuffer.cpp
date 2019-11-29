#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(FRAME_BUFFER_TYPE type, int width, int height, bool colorBuffer, bool depthBuffer, bool stencilBuffer)
{
	this->width = width;
	this->height = height;

	// 创建帧缓冲：颜色缓冲，深度缓冲，模板缓冲合起来叫做帧缓冲，之前我们使用的是默认帧缓冲
	glGenFramebuffers(1, &frameBuffer);
	// 绑定帧缓冲：之后所有读取和写入帧缓冲的操作都是对当前帧缓冲而言的
	if (type == READ_ADN_DRAW) {
		// 默认帧缓冲，读写都可以
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	}
	else if (type == READ) {
		// 只读缓冲
		glBindFramebuffer(GL_READ_FRAMEBUFFER, frameBuffer);
	}
	else {
		// 只写缓冲
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer);
	}

	// 添加颜色缓冲
	if (colorBuffer) {
		attachColorBuffer();
	}

	attachRenderBufferObject();
	
	// 检查帧缓冲是否完整
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "ERROR::FRAME_BUFFER::Framebuffer is not complete!\n" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
}

void FrameBuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int FrameBuffer::getTexture()
{
	return colorTexture;
}

void FrameBuffer::attachColorBuffer()
{
	// 创建帧缓冲需要的附件，这里使用一个纹理
	glGenTextures(1, &colorTexture);
	glBindTexture(GL_TEXTURE_2D, colorTexture);

	// 最后一个值为null，因为这个纹理是给帧缓冲用的，不需要初始化
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	// 设置线性缩放
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// 绑定纹理到帧缓冲（缓冲目标，附件类型，附加的纹理类型，附加的纹理，多级渐变纹理的级别）
	// 当然还可以绑定深度缓冲和模板缓冲，可选附件类型GL_DEPTH_ATTACHMENT，GL_STENCIL_ATTACHMENT，或GL_DEPTH_STENCIL_ATTACHMENT
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
}

void FrameBuffer::attachDepthBuffer()
{
}

void FrameBuffer::attachStencilBuffer()
{
}

void FrameBuffer::attachRenderBufferObject()
{
	// 创建渲染缓冲对象：只写，但是可以通过glReadPixels来读取他
	glGenRenderbuffers(1, &renderBufferObject);
	// 绑定渲染缓冲对象
	glBindRenderbuffer(GL_RENDERBUFFER, renderBufferObject);
	// 创建深度和渲染缓冲对象
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
	// 附加渲染缓冲对象
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject);
}
