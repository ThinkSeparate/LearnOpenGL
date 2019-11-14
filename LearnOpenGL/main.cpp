//----包含需要的外部库文件
#include <glad/glad.h>	// 用来管理OpenGL函数指针
#include <GLFW/glfw3.h>	// glfw3，包含了OpenGL的库使用

//----包含系统库文件
#include <iostream>

//----声明函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char* vertexShaderSource = 
// 使用OpenGL3.3版本，模式是核心渲染模式
"#version 330 core\n"
// in声明输入属性，即通过程序逻辑传递给GPU；layout (location = 0)用于在传递数值的时候定位属性的位置
// vec3是vector变量，有3个元素
"layout (location = 0) in vec3 aPos;\n"
"\n"
// mian函数是着色器程序的入口函数
"void main()\n"
"{\n"
// 顶点着色器的输出内容必须有gl_Position；这个值将用于渲染的下一步骤
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = 
"#version 330 core\n"
// out定义输出值，即传递给下一个渲染步骤的值
"out vec4 FragColor;\n"
"\n"
// 接受顶点着色器传过来的颜色
"uniform vec4 ourColor;\n"
"\n"
"void main()\n"
"{\n"
// OpenGL的rgba值为float类型，数值在0-1之间
"   FragColor = ourColor;\n"
"}\n\0";

int main() {

	// 初始化GLFW
	glfwInit();
	// 使用opengl3.3版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// 使用核心模式
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 创建一个800x600的窗口，窗口标题为LearnOpenGL
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// 将窗口设置为当前线程的上下文
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// 渲染窗口，左下角坐标（0， 0），宽高（800，600）
	// OpenGl的坐标范围（-1，1），此处映射到（800，600）
	//glViewport(0, 0, 800, 600);
	framebuffer_size_callback(window, 800, 600);

	float vertices[] = {
		0.5f, 0.5f, 0.0f,   // 右上角
		0.5f, -0.5f, 0.0f,  // 右下角
		-0.5f, -0.5f, 0.0f, // 左下角
		-0.5f, 0.5f, 0.0f   // 左上角
	};

	unsigned int indices[] = { // 注意索引从0开始! 
		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};

	// 生成顶点着色器对象
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// 绑定顶点着色器源码到顶点着色器对象上
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
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
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// 编译片段着色器
	glCompileShader(fragmentShader);

	// 获取片段着色器编译状态
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// 生成着色器程序对象
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	// 绑定着色器对象到着色器程序上
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// 链接着色器
	glLinkProgram(shaderProgram);

	// 获取着色器程序链接状态
	glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	// 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int VBO, VAO, EBO;
	// 生成VAO对象
	glGenVertexArrays(1, &VAO);
	// 生成VBO对象
	glGenBuffers(1, &VBO);
	// 生成VEO对象
	glGenBuffers(1, &EBO);

	// 绑定VAO
	glBindVertexArray(VAO);

	// 绑定VBO，并把数据复制到缓冲
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 绑定VEO，并把数据复制到缓冲
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 链接顶点属性
	// （要配置的顶点属性layout(location = 0)， 顶点属性的大小， 顶点属性的类型，步长（一个顶点属性的长度），偏移量（该属性在一个顶点数据中的起始位置））
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// 以顶点属性位置为参数启用顶点属性(location = 0)；顶点属性默认禁用
	glEnableVertexAttribArray(0);

	// 使用线框模式绘制
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// 查询可以使用的最大顶点属性个数
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	// 在每次循环渲染之前检查是否需要退出
	while (!glfwWindowShouldClose(window))
	{
		// 输入
		processInput(window);

		// 清屏
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 渲染
		// 使用着色器
		glUseProgram(shaderProgram);

		// 获得gl运行时间
		float timeValue = glfwGetTime();
		// 使用sin函数改变green指
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		// 获得需要传入属性的位置
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		// 传入属性，这个方法必须在glUseProgram方法后使用，4是指传入数据的个数，f是数据的类型
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		// 绑定顶点数组
		//glBindVertexArray(VAO);
		// 绘制三角形
		// （OpenGL图元， 顶点数组的起始索引，绘制顶点个数）
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		// (OpenGL图元，绘制顶点个数，索引类型，起始索引的位置)
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// 交换颜色缓冲，用来绘制（交换是因为双缓冲）
		glfwSwapBuffers(window);
		// 检查出发事件、更新窗口状态；并调用回调函数
		glfwPollEvents();
	}

	// 释放/删除之前的分配的所有资源
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