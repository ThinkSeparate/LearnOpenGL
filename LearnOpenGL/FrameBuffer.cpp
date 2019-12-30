#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(FRAME_BUFFER_TYPE type, int width, int height, bool colorBuffer, bool depthBuffer, bool stencilBuffer, bool mass, int samples)
{
	this->type = type;
	this->width = width;
	this->height = height;
	this->colorBuffer = colorBuffer;
	this->depthBuffer = depthBuffer;
	this->stencilBuffer = stencilBuffer;
	this->mass = mass;
	this->samples = samples;

	if (mass) {
		// 创建多重采样帧缓冲
		createMultiFrameBuffer();
	}

	// 创建帧缓冲
	createFrameBuffer();
}

void FrameBuffer::Bind()
{
	if (mass) {
		glBindFramebuffer(GL_FRAMEBUFFER, multiFrameBuffer);
	}
	else
	{
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	}
}

void FrameBuffer::Unbind()
{
	if (mass) {
		// 因为多重采样使用了更多的颜色信息，所以不能直接绘制到屏幕
		// 绑定多重采样为只读
		glBindFramebuffer(GL_READ_FRAMEBUFFER, multiFrameBuffer);
		// 绑定普通缓冲为只写
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer);
		// 这个函数会将多重采样缓冲的内容传送到普通缓冲中
		glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}
	else
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}

unsigned int FrameBuffer::getTexture()
{
	return colorTexture;
}

void FrameBuffer::createFrameBuffer()
{
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

void FrameBuffer::createMultiFrameBuffer()
{
	glGenFramebuffers(1, &multiFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, multiFrameBuffer);

	// 添加颜色缓冲
	attachMultiColorBuffer();
	// 添加渲染缓冲
	attachMultiRenderBufferObject();

	// 检查帧缓冲是否完整
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "ERROR::FRAME_BUFFER::Framebuffer is not complete!\n" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
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

void FrameBuffer::attachMultiColorBuffer()
{
	glGenTextures(1, &multiColorTexture);
	// 绑定未多重采样纹理
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, multiColorTexture);

	// 第二个参数为采样个数，最后一个参数GL_TRUE，图像将会对每个纹素使用相同的样本位置以及相同数量的子采样点个数。
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGB, width, height, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

	// 绑定到帧缓冲，纹理类型改成多重采样纹理
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, multiColorTexture, 0);
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
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	// 附加渲染缓冲对象
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject);
}

void FrameBuffer::attachMultiRenderBufferObject()
{
	glGenRenderbuffers(1, &multiRenderBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, multiRenderBufferObject);
	// 只是改变了存储方法，加入了采样数量
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, multiRenderBufferObject);
}
