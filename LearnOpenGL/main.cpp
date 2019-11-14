//----������Ҫ���ⲿ���ļ�
#include <glad/glad.h>	// ��������OpenGL����ָ��
#include <GLFW/glfw3.h>	// glfw3��������OpenGL�Ŀ�ʹ��

//----����ϵͳ���ļ�
#include <iostream>

//----��������
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char* vertexShaderSource = 
// ʹ��OpenGL3.3�汾��ģʽ�Ǻ�����Ⱦģʽ
"#version 330 core\n"
// in�����������ԣ���ͨ�������߼����ݸ�GPU��layout (location = 0)�����ڴ�����ֵ��ʱ��λ���Ե�λ��
// vec3��vector��������3��Ԫ��
"layout (location = 0) in vec3 aPos;\n"
"\n"
// mian��������ɫ���������ں���
"void main()\n"
"{\n"
// ������ɫ����������ݱ�����gl_Position�����ֵ��������Ⱦ����һ����
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = 
"#version 330 core\n"
// out�������ֵ�������ݸ���һ����Ⱦ�����ֵ
"out vec4 FragColor;\n"
"\n"
// ���ܶ�����ɫ������������ɫ
"uniform vec4 ourColor;\n"
"\n"
"void main()\n"
"{\n"
// OpenGL��rgbaֵΪfloat���ͣ���ֵ��0-1֮��
"   FragColor = ourColor;\n"
"}\n\0";

int main() {

	// ��ʼ��GLFW
	glfwInit();
	// ʹ��opengl3.3�汾
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// ʹ�ú���ģʽ
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ����һ��800x600�Ĵ��ڣ����ڱ���ΪLearnOpenGL
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// ����������Ϊ��ǰ�̵߳�������
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// ��Ⱦ���ڣ����½����꣨0�� 0������ߣ�800��600��
	// OpenGl�����귶Χ��-1��1�����˴�ӳ�䵽��800��600��
	//glViewport(0, 0, 800, 600);
	framebuffer_size_callback(window, 800, 600);

	float vertices[] = {
		0.5f, 0.5f, 0.0f,   // ���Ͻ�
		0.5f, -0.5f, 0.0f,  // ���½�
		-0.5f, -0.5f, 0.0f, // ���½�
		-0.5f, 0.5f, 0.0f   // ���Ͻ�
	};

	unsigned int indices[] = { // ע��������0��ʼ! 
		0, 1, 3, // ��һ��������
		1, 2, 3  // �ڶ���������
	};

	// ���ɶ�����ɫ������
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// �󶨶�����ɫ��Դ�뵽������ɫ��������
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// ���붥����ɫ��
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];

	// ��ȡ������ɫ������״̬
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// ����Ƭ����ɫ��
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// ��Ƭ����ɫ��Դ�뵽Ƭ����ɫ������
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// ����Ƭ����ɫ��
	glCompileShader(fragmentShader);

	// ��ȡƬ����ɫ������״̬
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// ������ɫ���������
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	// ����ɫ��������ɫ��������
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// ������ɫ��
	glLinkProgram(shaderProgram);

	// ��ȡ��ɫ����������״̬
	glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	// ɾ����ɫ���������Ѿ����ӵ����ǵĳ������ˣ��Ѿ�������Ҫ��
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int VBO, VAO, EBO;
	// ����VAO����
	glGenVertexArrays(1, &VAO);
	// ����VBO����
	glGenBuffers(1, &VBO);
	// ����VEO����
	glGenBuffers(1, &EBO);

	// ��VAO
	glBindVertexArray(VAO);

	// ��VBO���������ݸ��Ƶ�����
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ��VEO���������ݸ��Ƶ�����
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// ���Ӷ�������
	// ��Ҫ���õĶ�������layout(location = 0)�� �������ԵĴ�С�� �������Ե����ͣ�������һ���������Եĳ��ȣ���ƫ��������������һ�����������е���ʼλ�ã���
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// �Զ�������λ��Ϊ�������ö�������(location = 0)����������Ĭ�Ͻ���
	glEnableVertexAttribArray(0);

	// ʹ���߿�ģʽ����
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// ��ѯ����ʹ�õ���󶥵����Ը���
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	// ��ÿ��ѭ����Ⱦ֮ǰ����Ƿ���Ҫ�˳�
	while (!glfwWindowShouldClose(window))
	{
		// ����
		processInput(window);

		// ����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ��Ⱦ
		// ʹ����ɫ��
		glUseProgram(shaderProgram);

		// ���gl����ʱ��
		float timeValue = glfwGetTime();
		// ʹ��sin�����ı�greenָ
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		// �����Ҫ�������Ե�λ��
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		// �������ԣ��������������glUseProgram������ʹ�ã�4��ָ�������ݵĸ�����f�����ݵ�����
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		// �󶨶�������
		//glBindVertexArray(VAO);
		// ����������
		// ��OpenGLͼԪ�� �����������ʼ���������ƶ��������
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		// (OpenGLͼԪ�����ƶ���������������ͣ���ʼ������λ��)
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// ������ɫ���壬�������ƣ���������Ϊ˫���壩
		glfwSwapBuffers(window);
		// �������¼������´���״̬�������ûص�����
		glfwPollEvents();
	}

	// �ͷ�/ɾ��֮ǰ�ķ����������Դ
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}