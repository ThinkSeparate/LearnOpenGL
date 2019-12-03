#pragma once

#include <glad/glad.h>	// ��������OpenGL����ָ��
#include <GLFW/glfw3.h>	// glfw3��������OpenGL�Ŀ�ʹ��
#include <stb-master\stb_image.h> // ͼƬ���ؿ�

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class TextureLoader
{
public:
	unsigned int loadTexture(const char* path, bool flip = false);
	unsigned int loadSkyBox(vector<std::string> faces, bool flip = false);
private:
	unsigned int id;
	vector<std::string> faces;
};

