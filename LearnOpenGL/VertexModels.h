#pragma once

#include <glad/glad.h>	// ��������OpenGL����ָ��
#include <GLFW/glfw3.h>	// glfw3��������OpenGL�Ŀ�ʹ��

#include <glm/glm.hpp>	// ����OpenGL�任��صĿ��ļ���glm��OpenGL Mathematics����д
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <vector>
using namespace std;

#include "Shader.h"
#include "TextureLoader.h"

class VertexModels
{
public:
	VertexModels();
	void DrawBox(Shader shader);
	void DrawBoxes(Shader shader);
	void DrawGrass(Shader shader);
	void DrawPlane(Shader shader);
	void DrawScreen(Shader shader);
	void DrawSkyBox(Shader shader);
	void DrawPoints(Shader shader);
private:
	TextureLoader textureLoader;
	glm::mat4 model;
	vector<glm::vec3> vegetation;
	unsigned int boxVAO, boxVBO;
	unsigned int cubeVAO, cubeVBO;
	unsigned int vegetationVAO, vegetationVBO;
	unsigned int planeVAO, planeVBO;
	unsigned int screenVAO, screenVBO;
	unsigned int skyVAO, skyVBO;
	unsigned int pointVAO, pointVBO;
	void InitBox();
	void InitBoxes();
	void InitGrass();
	void InitPlane();
	void InitScreen();
	void InitSkyBox();
	void InitPoints();
};

