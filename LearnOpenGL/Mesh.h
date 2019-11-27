#pragma once

#include <glm/glm.hpp>	// 引用OpenGL变换相关的库文件，glm是OpenGL Mathematics的缩写
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
	/*	网格数据	*/
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	/*	函数	*/
	Mesh(vector<Vertex> vertexes, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(Shader shader);
private:
	/*	渲染数据	*/
	unsigned int VAO, VBO, EBO;
	/*	函数	*/
	void setupMesh();
};

