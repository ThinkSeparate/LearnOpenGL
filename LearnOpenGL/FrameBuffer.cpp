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
		// �������ز���֡����
		createMultiFrameBuffer();
	}

	// ����֡����
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
		// ��Ϊ���ز���ʹ���˸������ɫ��Ϣ�����Բ���ֱ�ӻ��Ƶ���Ļ
		// �󶨶��ز���Ϊֻ��
		glBindFramebuffer(GL_READ_FRAMEBUFFER, multiFrameBuffer);
		// ����ͨ����Ϊֻд
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer);
		// ��������Ὣ���ز�����������ݴ��͵���ͨ������
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
	// ����֡���壺��ɫ���壬��Ȼ��壬ģ�建�����������֡���壬֮ǰ����ʹ�õ���Ĭ��֡����
	glGenFramebuffers(1, &frameBuffer);
	// ��֡���壺֮�����ж�ȡ��д��֡����Ĳ������ǶԵ�ǰ֡������Ե�
	if (type == READ_ADN_DRAW) {
		// Ĭ��֡���壬��д������
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	}
	else if (type == READ) {
		// ֻ������
		glBindFramebuffer(GL_READ_FRAMEBUFFER, frameBuffer);
	}
	else {
		// ֻд����
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer);
	}

	// �����ɫ����
	if (colorBuffer) {
		attachColorBuffer();
	}

	attachRenderBufferObject();

	// ���֡�����Ƿ�����
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "ERROR::FRAME_BUFFER::Framebuffer is not complete!\n" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::createMultiFrameBuffer()
{
	glGenFramebuffers(1, &multiFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, multiFrameBuffer);

	// �����ɫ����
	attachMultiColorBuffer();
	// �����Ⱦ����
	attachMultiRenderBufferObject();

	// ���֡�����Ƿ�����
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "ERROR::FRAME_BUFFER::Framebuffer is not complete!\n" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::attachColorBuffer()
{
	// ����֡������Ҫ�ĸ���������ʹ��һ������
	glGenTextures(1, &colorTexture);
	glBindTexture(GL_TEXTURE_2D, colorTexture);

	// ���һ��ֵΪnull����Ϊ��������Ǹ�֡�����õģ�����Ҫ��ʼ��
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	// ������������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// ������֡���壨����Ŀ�꣬�������ͣ����ӵ��������ͣ����ӵ������༶��������ļ���
	// ��Ȼ�����԰���Ȼ����ģ�建�壬��ѡ��������GL_DEPTH_ATTACHMENT��GL_STENCIL_ATTACHMENT����GL_DEPTH_STENCIL_ATTACHMENT
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
}

void FrameBuffer::attachMultiColorBuffer()
{
	glGenTextures(1, &multiColorTexture);
	// ��δ���ز�������
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, multiColorTexture);

	// �ڶ�������Ϊ�������������һ������GL_TRUE��ͼ�񽫻��ÿ������ʹ����ͬ������λ���Լ���ͬ�������Ӳ����������
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGB, width, height, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

	// �󶨵�֡���壬�������͸ĳɶ��ز�������
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
	// ������Ⱦ�������ֻд�����ǿ���ͨ��glReadPixels����ȡ��
	glGenRenderbuffers(1, &renderBufferObject);
	// ����Ⱦ�������
	glBindRenderbuffer(GL_RENDERBUFFER, renderBufferObject);
	// ������Ⱥ���Ⱦ�������
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	// ������Ⱦ�������
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject);
}

void FrameBuffer::attachMultiRenderBufferObject()
{
	glGenRenderbuffers(1, &multiRenderBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, multiRenderBufferObject);
	// ֻ�Ǹı��˴洢�����������˲�������
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, multiRenderBufferObject);
}
