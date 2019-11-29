#pragma once

#include <glad/glad.h>	// ��������OpenGL����ָ��
#include <GLFW/glfw3.h>	// glfw3��������OpenGL�Ŀ�ʹ��
#include <stb-master\stb_image.h> // ͼƬ���ؿ�

#include <iostream>
#include <vector>
using namespace std;

class SkyBox
{
public:
	SkyBox(vector<std::string> faces);
	unsigned int getTexture();
private:
	unsigned int textureID;
	vector<std::string> faces;
};

