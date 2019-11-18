//----包含需要的外部库文件
#include <glad/glad.h>	// 用来管理OpenGL函数指针
#include <GLFW/glfw3.h>	// glfw3，包含了OpenGL的库使用
#include <stb-master\stb_image.h> // 图片加载库
#include <glm/glm.hpp>	// 引用OpenGL变换相关的库文件，glm是OpenGL Mathematics的缩写
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

//----包含系统库文件
#include <iostream>

//----包含自定义类
#include "Shader.h"	// 引用shader类
#include "TechnologyTest.h"	// 自定义的技术测试类：学习中需要使用很多新技术，测试性代码放在这个类里实现

//----声明常量
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//----声明函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

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
	framebuffer_size_callback(window, SCR_WIDTH, SCR_HEIGHT);

	float vertices[] = {
		//     ---- 位置 ----     - 纹理坐标 -
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int indices[] = { // 注意索引从0开始! 
		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	// 加载墙的图片
	int width, height, nrChannels;
	unsigned char* data1 = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);

	// 生成纹理对象
	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);
	// 绑定纹理
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (data1) {
		// 生成纹理
		// （纹理目标，纹理渐变级别，存储格式，纹理宽度，纹理高度，0，源数据格式，源数据类型， 图像数据）
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
		// 生成多级渐变纹理
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	// 翻转y轴
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);

	glGenTextures(1, &texture2);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (data2) {
		// 生成纹理
		// （纹理目标，纹理渐变级别，存储格式，纹理宽度，纹理高度，0，源数据格式，源数据类型， 图像数据）
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		// 生成多级渐变纹理
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	// 释放图像内存
	stbi_image_free(data1);
	stbi_image_free(data2);

	Shader shader("vertex.glsl", "fragment.glsl");

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	// 以顶点属性位置为参数启用顶点属性(location = 0)；顶点属性默认禁用
	glEnableVertexAttribArray(0);

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// 技术测试
	TechnologyTest technologyTest;
	technologyTest.testAll();

	// 在每次循环渲染之前检查是否需要退出
	while (!glfwWindowShouldClose(window))
	{
		// 输入
		processInput(window);

		// 启用深度测试，解决绘制物体穿模问题,这个实际只需要执行一次就可以了，只有在不断切换开启和关闭状态时才需要不断变换
		glEnable(GL_DEPTH_TEST);

		// 清屏
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// 清除深度缓存是每一帧都要执行的，如果你希望绘制正确
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 渲染
		// 使用着色器
		shader.use();
		
		// 创建观察矩阵
		glm::mat4 view;
		// 反向移动观察矩阵，即将模型远离摄像机
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		// 创建投影矩阵
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		// 将矩阵传入顶点着色器，计算顶点坐标
		
		shader.setMatrix4("view", glm::value_ptr(view));
		shader.setMatrix4("projection", glm::value_ptr(projection));
		// 绑定纹理并绘制
		shader.setInt("ourTexture1", 0);
		shader.setInt("ourTexture2", 1);

		// 绑定顶点数组
		glBindVertexArray(VAO);
		// 绘制三角形
		// （OpenGL图元， 顶点数组的起始索引，绘制顶点个数）
		for (unsigned int i = 0; i < 10; i++) {
			//创建模型矩阵
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			// 将模型以x轴旋转-55度
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
			shader.setMatrix4("model", glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	
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