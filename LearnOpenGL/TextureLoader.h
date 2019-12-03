#pragma once

#include <glad/glad.h>	// 用来管理OpenGL函数指针
#include <GLFW/glfw3.h>	// glfw3，包含了OpenGL的库使用
#include <stb-master\stb_image.h> // 图片加载库

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

