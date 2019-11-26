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
#include "Camera.h"	// 引用摄像机类
#include "Shader.h"	// 引用shader类
#include "TechnologyTest.h"	// 自定义的技术测试类：学习中需要使用很多新技术，测试性代码放在这个类里实现

//----声明常量
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//----声明函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

//----定义全局变量
// 摄像机
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
// 用来计算鼠标的偏移量，初始值设置为屏幕中心
float lastX = SCR_WIDTH/2.0f, lastY = SCR_HEIGHT/2.0f;
// 声明一个变量，用来解决第一次进入窗口，偏移量计算过大问题
bool firstMouse = true;

// 这两个变量用来解决每帧时间问题
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

// 定义灯的位置
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main() {

	// 初始化GLFW
	glfwInit();
	// 使用opengl3.3版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// 使用核心模式
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 创建一个800x600的窗口，窗口标题为LearnOpenGL
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
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

	// 生成纹理对象
	unsigned int diffuseMap, specularMap;
	glGenTextures(1, &diffuseMap);
	// 绑定纹理
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);

	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// 加载墙的图片
	int width, height, nrChannels;
	//stbi_set_flip_vertically_on_load(true);
	unsigned char* data1 = stbi_load("container2.png", &width, &height, &nrChannels, 0);

	if (data1) {
		// 生成纹理
		// （纹理目标，纹理渐变级别，存储格式，纹理宽度，纹理高度，0，源数据格式，源数据类型， 图像数据）
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
		// 生成多级渐变纹理
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	// 生成纹理对象
	glGenTextures(1, &specularMap);
	// 绑定纹理
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularMap);

	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// 加载镜面反射的图片
	//stbi_set_flip_vertically_on_load(true);
	unsigned char* data2 = stbi_load("container2_specular.png", &width, &height, &nrChannels, 0);

	if (data2) {
		// 生成纹理
		// （纹理目标，纹理渐变级别，存储格式，纹理宽度，纹理高度，0，源数据格式，源数据类型， 图像数据）
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
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
	Shader lightShader("lightVertex.glsl", "lightFragment.glsl");

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	// 以顶点属性位置为参数启用顶点属性(location = 0)；顶点属性默认禁用
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//	创建灯光VAO
	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	// 只需要绑定VBO不用再次设置VBO的数据，因为箱子的VBO数据中已经包含了正确的立方体顶点数据
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	// 设置灯立方体的顶点属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// 技术测试
	TechnologyTest technologyTest;
	technologyTest.TestAll();

	// 在每次循环渲染之前检查是否需要退出
	while (!glfwWindowShouldClose(window))
	{
		// 更新当前帧时间
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// 输入
		processInput(window);

		// 启用深度测试，解决绘制物体穿模问题,这个实际只需要执行一次就可以了，只有在不断切换开启和关闭状态时才需要不断变换
		glEnable(GL_DEPTH_TEST);

		// 清屏
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// 清除深度缓存是每一帧都要执行的，如果你希望绘制正确
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 渲染
		// 创建观察矩阵(摄像机)
		glm::mat4 view = camera.getViewMatrix();

		// 创建投影矩阵
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		// 处理灯的位置
		glm::mat4 model;
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));

		// 使用灯着色器
		lightShader.Use();
		lightShader.setMatrix4("view", glm::value_ptr(view));
		lightShader.setMatrix4("projection", glm::value_ptr(projection));
		lightShader.setMatrix4("model", glm::value_ptr(model));

		// 绘制灯
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 使用着色器
		shader.Use();
		shader.setFloat("objectColor", 1.0f, 0.5f, 0.31f);
		shader.setFloat("lightColor", 1.0f, 1.0f, 1.0f);
		shader.setFloat("lightPos", lightPos);
		shader.setFloat("viewPos", camera.getPosition());

		// 设置变化的光源
		glm::vec3 lightColor;
		lightColor.x = sin(glfwGetTime() * 2.0f);
		lightColor.y = sin(glfwGetTime() * 0.7f);
		lightColor.z = sin(glfwGetTime() * 1.3f);

		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // 降低影响
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // 很低的影响

		shader.setFloat("light.direction", -0.2f, -1.0f, -0.3f);
		shader.setFloat("light.ambient", ambientColor);
		shader.setFloat("light.diffuse", diffuseColor); // 将光照调暗了一些以搭配场景
		shader.setFloat("light.specular", 1.0f, 1.0f, 1.0f);

		shader.setFloat("light.constant", 1.0f);
		shader.setFloat("light.linear", 0.09f);
		shader.setFloat("light.quadratic", 0.032f);

		shader.setFloat("material.ambient", 1.0f, 0.5f, 0.31f);
		shader.setFloat("material.diffuse", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		shader.setFloat("material.specular", 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		shader.setFloat("material.shininess", 32.0f);
		// 绑定纹理并绘制
		shader.setInt("ourTexture1", 0);
		shader.setInt("ourTexture2", 1);

		// 将矩阵传入顶点着色器，计算顶点坐标
		shader.setMatrix4("view", glm::value_ptr(view));
		shader.setMatrix4("projection", glm::value_ptr(projection));

		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
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
	// 隐藏光标并捕捉他（如果你发现鼠标不见了）
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	// 监听鼠标操作
	glfwSetCursorPosCallback(window, mouse_callback);

	// 滚轮监听
	glfwSetScrollCallback(window, scroll_callback);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
	float cameraSpeed = 2.5f * deltaTime;
	// w键，向前移动
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	// s键，向后移动
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	// a键，向左移动
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	// d键，向右移动
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}

// 鼠标事件
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse) // 这个bool变量初始时是设定为true的
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	// 计算偏移量
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;	// 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
	// 更新上一次的鼠标位置
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}