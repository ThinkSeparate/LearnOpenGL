#include "TechnologyTest.h"

void TechnologyTest::testAll()
{
	//testPolygonMode();
	testMaxVertexAttribs();
	testMatrix();
}

void TechnologyTest::testPolygonMode()
{
	// 使用线框模式绘制
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void TechnologyTest::testMaxVertexAttribs()
{
	// 查询可以使用的最大顶点属性个数
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
}

void TechnologyTest::testMatrix()
{
	/*	glm测试代码	*/
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	// 初始化一个默认的平移矩阵
	glm::mat4 trans;
	// 对平移变换矩阵设置平移
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	// 用平移矩阵操作我们的测试矩阵
	vec = trans * vec;
	std::cout << vec.x << vec.y << vec.z << std::endl;
}
