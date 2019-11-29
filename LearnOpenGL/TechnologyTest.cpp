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
	// 使用线框模式绘制
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void TechnologyTest::TestMaxVertexAttribs()
{
	// 查询可以使用的最大顶点属性个数
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
}

void TechnologyTest::TestMatrix()
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

void TechnologyTest::TestDepthTest()
{
	// 首先要开启深度测试
	glEnable(GL_DEPTH_TEST);
	// 设置深度缓冲为只读类型
	//glDepthMask(GL_FALSE);
	// 设置深度测试通过条件：其他测试条件略
	glDepthFunc(GL_LESS);
}

void TechnologyTest::TestStenchTest()
{
	// 启动模板测试
	glEnable(GL_STENCIL_TEST);
	// 设置模板测试掩码，掩码会与写入缓冲的模板做AND运算。
	//glStencilMask(0x00);
	// (测试条件（可选值：GL_NEVER、GL_LESS、GL_LEQUAL、GL_GREATER、GL_GEQUAL、GL_EQUAL、GL_NOTEQUAL和GL_ALWAYS），参考值（模板测试时用来比较的标准值），mask)
	// 这条命令实际上定义了一个比较关系（模板值&mask后与参考值比较，并使用测试条件输出比较结果）
	//glStencilFunc(GL_EQUAL, 1, 0xFF);
	/*  如何更新缓冲（模板测试失败时采取的行动，模板测试通过单深度测试失败时采取的行动，模板测试和深度测试都通过时采取的行动）
		GL_KEEP 保持当前储存的模板值
		GL_ZERO 将模板值设置为0
		GL_REPLACE 将模板值设置为glStencilFunc函数设置的ref值
		GL_INCR 如果模板值小于最大值则将模板值加1
		GL_INCR_WRAP 与GL_INCR一样，但如果模板值超过了最大值则归零
		GL_DECR 如果模板值大于最小值则将模板值减1
		GL_DECR_WRAP 与GL_DECR一样，但如果模板值小于0则将其设置为最大值
		GL_INVERT 按位翻转当前的模板缓冲值 */
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
}
