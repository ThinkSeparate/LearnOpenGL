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
	void testAll();
private:
	void testPolygonMode();
	void testMaxVertexAttribs();
	void testMatrix();
};

