#pragma once

#include <glad\glad.h>

#include <glm/glm.hpp>	// 引用OpenGL变换相关的库文件，glm是OpenGL Mathematics的缩写
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
public:
	// const关键字 不可修改
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	Shader(const GLchar* vertexPath, const GLchar* geometricPath, const GLchar* fragmentPath);
	// 使用/激活程序
	void Use();
	// uniform工具函数
	void setBool(const std::string& name, bool value1) const;
	void setBool(const std::string& name, bool value1, bool value2) const;
	void setBool(const std::string& name, bool value1, bool value2, bool value3) const;
	void setBool(const std::string& name, bool value1, bool value2, bool value3, bool value4) const;
	void setInt(const std::string& name, int value1) const;
	void setInt(const std::string& name, int value1, int value2) const;
	void setInt(const std::string& name, int value1, int value2, int value3) const;
	void setInt(const std::string& name, int value1, int value2, int value3, int value4) const;
	void setFloat(const std::string& name, glm::vec3 value) const;
	void setFloat(const std::string& name, float value1) const;
	void setFloat(const std::string& name, float value1, float value2) const;
	void setFloat(const std::string& name, glm::vec2 vec2) const;
	void setFloat(const std::string& name, float value1, float value2, float value3) const;
	void setFloat(const std::string& name, float value1, float value2, float value3, float value4) const;
	void setMatrix4(const std::string& name, GLfloat* matrix) const;
	~Shader();
private:
	// 着色器
	unsigned int vertexShader;
	unsigned int gemoetricShader;
	unsigned int fragmentShader;
	// 程序ID
	unsigned int ID;
	// 状态
	int success;	// 成功状态
	char infoLog[512];	// 错误信息
	std::string LoadShaderCode(const GLchar* shaderPath, std::string shaderType);
	void GenVertexShader(std::string vertexCode);
	void GenGeometricShader(std::string geometricCode);
	void GenFragmentShader(std::string fragmentCode);
};

