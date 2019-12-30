#pragma once

#include <glad\glad.h>

#include <glm/glm.hpp>	// ����OpenGL�任��صĿ��ļ���glm��OpenGL Mathematics����д
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
public:
	// const�ؼ��� �����޸�
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	Shader(const GLchar* vertexPath, const GLchar* geometricPath, const GLchar* fragmentPath);
	// ʹ��/�������
	void Use();
	// uniform���ߺ���
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
	// ��ɫ��
	unsigned int vertexShader;
	unsigned int gemoetricShader;
	unsigned int fragmentShader;
	// ����ID
	unsigned int ID;
	// ״̬
	int success;	// �ɹ�״̬
	char infoLog[512];	// ������Ϣ
	std::string LoadShaderCode(const GLchar* shaderPath, std::string shaderType);
	void GenVertexShader(std::string vertexCode);
	void GenGeometricShader(std::string geometricCode);
	void GenFragmentShader(std::string fragmentCode);
};

