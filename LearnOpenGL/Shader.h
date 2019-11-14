#pragma once

#include <glad\glad.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
public:
	// 程序ID
	unsigned int ID;

	// const关键字 不可修改
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	// 使用/激活程序
	void use();
	// uniform工具函数
	void setBool(const std::string& name, bool value1) const;
	void setBool(const std::string& name, bool value1, bool value2) const;
	void setBool(const std::string& name, bool value1, bool value2, bool value3) const;
	void setBool(const std::string& name, bool value1, bool value2, bool value3, bool value4) const;
	void setInt(const std::string& name, int value1) const;
	void setInt(const std::string& name, int value1, int value2) const;
	void setInt(const std::string& name, int value1, int value2, int value3) const;
	void setInt(const std::string& name, int value1, int value2, int value3, int value4) const;
	void setFloat(const std::string& name, float value1) const;
	void setFloat(const std::string& name, float value1, float value2) const;
	void setFloat(const std::string& name, float value1, float value2, float value3) const;
	void setFloat(const std::string& name, float value1, float value2, float value3, float value4) const;
	void setMatrix4(const std::string& name, GLfloat* matrix) const;
	~Shader();
};

