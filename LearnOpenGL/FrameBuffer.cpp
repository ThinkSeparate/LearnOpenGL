#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(FRAME_BUFFER_TYPE type, int width, int height, bool colorBuffer, bool depthBuffer, bool stencilBuffer)
{
	this->width = width;
	this->height = height;

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
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
	// ������Ⱦ�������
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject);
}
