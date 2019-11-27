#include "Mesh.h"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}

void Mesh::Draw(Shader shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++) {
		// ��������Ԫ
		glActiveTexture(GL_TEXTURE0 + i);
		// ��ȡ������ţ�diffuse_textureN �е� N��
		string number;
		string name = textures[i].type; 
		if (name == "texture_diffuse") {
			number = std::to_string(diffuseNr++);
		}
		else
		{
			number = std::to_string(specularNr++);
		}

		shader.setFloat(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	// ��������
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::setupMesh()
{
	// ����VAO����
	glGenVertexArrays(1, &VAO);
	// ����VBO����
	glGenBuffers(1, &VBO);
	// ����VEO����
	glGenBuffers(1, &EBO);

	// ��VAO
	glBindVertexArray(VAO);

	// ��VBO���������ݸ��Ƶ�����
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	// ��VEO���������ݸ��Ƶ�����
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// ���Ӷ�������
	// ��Ҫ���õĶ�������layout(location = 0)�� �������ԵĴ�С�� �������Ե����ͣ�������һ���������Եĳ��ȣ���ƫ��������������һ�����������е���ʼλ�ã���
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// �Զ�������λ��Ϊ�������ö�������(location = 0)����������Ĭ�Ͻ���
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}
