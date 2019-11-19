#include "TechnologyTest.h"

void TechnologyTest::TestAll()
{
	//testPolygonMode();
	TestMaxVertexAttribs();
	TestMatrix();
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
