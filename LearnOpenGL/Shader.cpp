#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	// �����ļ����ַ���
	std::string vertexCode = LoadShaderCode(vertexPath, "VERTEX");
	std::string fragmentCode = LoadShaderCode(fragmentPath, "FRAGMENT");

	// ������ɫ������
	GenVertexShader(vertexCode);
	GenFragmentShader(fragmentCode);

	// ������ɫ���������
	ID = glCreateProgram();
	// ����ɫ��������ɫ��������
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// ������ɫ��
	glLinkProgram(ID);

	// ��ȡ��ɫ����������״̬
	glGetShaderiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	// ɾ����ɫ���������Ѿ����ӵ����ǵĳ������ˣ��Ѿ�������Ҫ��
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::Shader(const GLchar* vertexPath, const GLchar* geometricPath, const GLchar* fragmentPath)
{
	// ������ɫ�������ַ������ļ�ָ��
	std::string vertexCode = LoadShaderCode(vertexPath, "VERTEX");
	std::string geometricCode = LoadShaderCode(geometricPath, "GEOMETRIC");
	std::string fragmentCode = LoadShaderCode(fragmentPath, "FRAGMENT");

	// ������ɫ������
	GenVertexShader(vertexCode);
	GenGeometricShader(geometricCode);
	GenFragmentShader(fragmentCode);

	// ������ɫ���������
	ID = glCreateProgram();
	// ����ɫ��������ɫ��������
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, gemoetricShader);
	glAttachShader(ID, fragmentShader);
	// ������ɫ��
	glLinkProgram(ID);

	// ��ȡ��ɫ����������״̬
	glGetShaderiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	// ɾ����ɫ���������Ѿ����ӵ����ǵĳ������ˣ��Ѿ�������Ҫ��
	glDeleteShader(vertexShader);
	glDeleteShader(gemoetricShader);
	glDeleteShader(fragmentShader);
}

void Shader::Use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value1) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value1);
}

void Shader::setBool(const std::string& name, bool value1, bool value2) const
{
	glUniform2i(glGetUniformLocation(ID, name.c_str()), (int)value1, (int)value2);
}

void Shader::setBool(const std::string& name, bool value1, bool value2, bool value3) const
{
	glUniform3i(glGetUniformLocation(ID, name.c_str()), (int)value1, (int)value2, (int)value3);
}

void Shader::setBool(const std::string& name, bool value1, bool value2, bool value3, bool value4) const
{
	glUniform4i(glGetUniformLocation(ID, name.c_str()), (int)value1, (int)value2, (int)value3, (int)value4);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setInt(const std::string& name, int value1, int value2) const
{
	glUniform2i(glGetUniformLocation(ID, name.c_str()), value1, value2);
}

void Shader::setInt(const std::string& name, int value1, int value2, int value3) const
{
	glUniform3i(glGetUniformLocation(ID, name.c_str()), value1, value2, value3);
}

void Shader::setInt(const std::string& name, int value1, int value2, int value3, int value4) const
{
	glUniform4i(glGetUniformLocation(ID, name.c_str()), value1, value2, value3, value4);
}

void Shader::setFloat(const std::string& name, glm::vec3 value) const
{
	setFloat(name, value.x, value.y, value.z);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);

}

void Shader::setFloat(const std::string& name, float value1, float value2) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), value1, value2);
}

void Shader::setFloat(const std::string& name, float value1, float value2, float value3) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3);
}

void Shader::setFloat(const std::string& name, float value1, float value2, float value3, float value4) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), value1, value2, value3, value4);
}

void Shader::setMatrix4(const std::string& name, GLfloat* matrix) const
{
	// ��������ַ������������Ƿ���Ҫת�þ��󣬾������ݣ�
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, matrix);
}

Shader::~Shader()
{
}

std::string Shader::LoadShaderCode(const GLchar* shaderPath, std::string shaderType)
{
	// ������ɫ�������ַ������ļ�ָ��
	std::string shaderCode;
	std::ifstream shaderFile;

	// ��֤ifstream��������׳��쳣
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// ���ļ�
		shaderFile.open(shaderPath);
		std::stringstream shaderStream;
		// ��ȡ�ļ��Ļ������ݵ���
		shaderStream << shaderFile.rdbuf();
		// �ر��ļ�������
		shaderFile.close();
		// ת����������string
		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::" << shaderType << "::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	return shaderCode;
}

void Shader::GenVertexShader(std::string vertexCode)
{
	const char* vShaderCode = vertexCode.c_str();

	// ���ɶ�����ɫ������
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// �󶨶�����ɫ��Դ�뵽������ɫ��������
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	// ���붥����ɫ��
	glCompileShader(vertexShader);

	// ��ȡ������ɫ������״̬
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::GenGeometricShader(std::string geometricCode)
{
	const char* gShaderCode = geometricCode.c_str();

	// ���ɼ�����ɫ������
	gemoetricShader = glCreateShader(GL_GEOMETRY_SHADER);

	// �󶨼�����ɫ��Դ�뵽������ɫ��������
	glShaderSource(gemoetricShader, 1, &gShaderCode, NULL);
	// ���뼸����ɫ��
	glCompileShader(gemoetricShader);

	// ��ȡ������ɫ������״̬
	glGetShaderiv(gemoetricShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(gemoetricShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::GEOMETRIC::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::GenFragmentShader(std::string fragmentCode)
{
	const char* fShaderCode = fragmentCode.c_str();

	// ����Ƭ����ɫ��
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// ��Ƭ����ɫ��Դ�뵽Ƭ����ɫ������
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	// ����Ƭ����ɫ��
	glCompileShader(fragmentShader);

	// ��ȡƬ����ɫ������״̬
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}
