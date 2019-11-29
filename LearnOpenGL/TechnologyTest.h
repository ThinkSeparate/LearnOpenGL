#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <iostream>

class TechnologyTest
{
public:
	void TestAll();
private:
	void TestPolygonMode();
	void TestMaxVertexAttribs();
	void TestMatrix();
	void TestDepthTest();
	void TestStenchTest();
	void TestBlend();
};

