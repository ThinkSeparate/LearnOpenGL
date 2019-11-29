#pragma once

#include <glad/glad.h>	// 用来管理OpenGL函数指针
#include <GLFW/glfw3.h>	// glfw3，包含了OpenGL的库使用
#include <stb-master\stb_image.h> // 图片加载库

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

