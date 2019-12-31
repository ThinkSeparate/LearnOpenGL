#pragma once

#include <stb-master\stb_image.h> // ͼƬ���ؿ�

#include <assimp/Importer.hpp>	// assimpģ�ͽ�����
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
using namespace std;

#include "Shader.h"
#include "Mesh.h"

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

class Model
{
public:
	Model(string path);
	void Draw(Shader shader);
	vector<Mesh> getMeshs();
	int getMeshsSize();
	Mesh getMesh(int index);
private:
	/*	ģ������	*/
	vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	vector<Mesh> meshes;
	string directory;
	/*	����	*/
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};

