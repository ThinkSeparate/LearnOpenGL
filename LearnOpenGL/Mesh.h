#pragma once

#include <glm/glm.hpp>	// ����OpenGL�任��صĿ��ļ���glm��OpenGL Mathematics����д
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <string>
#include <vector>
using namespace std;

#include "Shader.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct Texture
{
	unsigned int id;
	string type;
};

class Mesh
{
public:
	/*	��������	*/
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	/*	����	*/
	Mesh(vector<Vertex> vertexes, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(Shader shader);
private:
	/*	��Ⱦ����	*/
	unsigned int VAO, VBO, EBO;
	/*	����	*/
	void setupMesh();
};

