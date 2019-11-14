#pragma once

#include <glad\glad.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
public:
	// ����ID
	unsigned int ID;

	// const�ؼ��� �����޸�
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	// ʹ��/�������
	void use();
	// uniform���ߺ���
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

