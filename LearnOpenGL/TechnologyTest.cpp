#include "TechnologyTest.h"

void TechnologyTest::TestAll()
{
	//testPolygonMode();
	TestMaxVertexAttribs();
	TestMatrix();
	TestDepthTest();
	//TestStenchTest();
}

void TechnologyTest::TestPolygonMode()
{
	// ʹ���߿�ģʽ����
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void TechnologyTest::TestMaxVertexAttribs()
{
	// ��ѯ����ʹ�õ���󶥵����Ը���
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
}

void TechnologyTest::TestMatrix()
{
	/*	glm���Դ���	*/
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	// ��ʼ��һ��Ĭ�ϵ�ƽ�ƾ���
	glm::mat4 trans;
	// ��ƽ�Ʊ任��������ƽ��
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	// ��ƽ�ƾ���������ǵĲ��Ծ���
	vec = trans * vec;
	std::cout << vec.x << vec.y << vec.z << std::endl;
}

void TechnologyTest::TestDepthTest()
{
	// ����Ҫ������Ȳ���
	glEnable(GL_DEPTH_TEST);
	// ������Ȼ���Ϊֻ������
	//glDepthMask(GL_FALSE);
	// ������Ȳ���ͨ����������������������
	glDepthFunc(GL_LESS);
}

void TechnologyTest::TestStenchTest()
{
	// ����ģ�����
	glEnable(GL_STENCIL_TEST);
	// ����ģ��������룬�������д�뻺���ģ����AND���㡣
	//glStencilMask(0x00);
	// (������������ѡֵ��GL_NEVER��GL_LESS��GL_LEQUAL��GL_GREATER��GL_GEQUAL��GL_EQUAL��GL_NOTEQUAL��GL_ALWAYS�����ο�ֵ��ģ�����ʱ�����Ƚϵı�׼ֵ����mask)
	// ��������ʵ���϶�����һ���ȽϹ�ϵ��ģ��ֵ&mask����ο�ֵ�Ƚϣ���ʹ�ò�����������ȽϽ����
	//glStencilFunc(GL_EQUAL, 1, 0xFF);
	/*  ��θ��»��壨ģ�����ʧ��ʱ��ȡ���ж���ģ�����ͨ������Ȳ���ʧ��ʱ��ȡ���ж���ģ����Ժ���Ȳ��Զ�ͨ��ʱ��ȡ���ж���
		GL_KEEP ���ֵ�ǰ�����ģ��ֵ
		GL_ZERO ��ģ��ֵ����Ϊ0
		GL_REPLACE ��ģ��ֵ����ΪglStencilFunc�������õ�refֵ
		GL_INCR ���ģ��ֵС�����ֵ��ģ��ֵ��1
		GL_INCR_WRAP ��GL_INCRһ���������ģ��ֵ���������ֵ�����
		GL_DECR ���ģ��ֵ������Сֵ��ģ��ֵ��1
		GL_DECR_WRAP ��GL_DECRһ���������ģ��ֵС��0��������Ϊ���ֵ
		GL_INVERT ��λ��ת��ǰ��ģ�建��ֵ */
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
}
