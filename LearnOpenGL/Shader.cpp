#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	// 声明着色器代码字符串和文件指针
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	// 保证ifstream对象可以抛出异常
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// 打开文件
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// 读取文件的缓存内容到流
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// 关闭文件处理器
		vShaderFile.close();
		fShaderFile.close();
		// 转换数据流到string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// 生成顶点着色器对象
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// 绑定顶点着色器源码到顶点着色器对象上
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	// 编译顶点着色器
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];

	// 获取顶点着色器编译状态
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// 生成片段着色器
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// 绑定片段着色器源码到片段着色器对象
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	// 编译片段着色器
	glCompileShader(fragmentShader);

	// 获取片段着色器编译状态
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// 生成着色器程序对象
	ID = glCreateProgram();
	// 绑定着色器对象到着色器程序上
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// 链接着色器
	glLinkProgram(ID);

	// 获取着色器程序链接状态
	glGetShaderiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	// 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
	glDeleteShader(vertexShader);
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
	// （变量地址，矩阵个数，是否需要转置矩阵，矩阵数据）
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, matrix);
}

Shader::~Shader()
{
}
