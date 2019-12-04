//----包含需要的外部库文件
#include <glad/glad.h>	// 用来管理OpenGL函数指针
#include <GLFW/glfw3.h>	// glfw3，包含了OpenGL的库使用
#include <stb-master\stb_image.h> // 图片加载库

#include <glm/glm.hpp>	// 引用OpenGL变换相关的库文件，glm是OpenGL Mathematics的缩写
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

//----包含系统库文件
#include <iostream>
#include <string>

//----包含自定义类
#include "FrameBuffer.h"
#include "Camera.h"	// 引用摄像机类
#include "Shader.h"	// 引用shader类
#include "Model.h"
#include "VertexModels.h"
#include "TextureLoader.h"
#include "SkyBox.h"
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
	
	// 生成shader对象
	Shader shader("model.vert", "model.geom", "model.frag");
	// 生成顶点模型shader
	Shader vertexModelShader("vertex.vert", "vertex.frag");
	// 创建轮廓shader
	Shader outlineShader("outline.vert", "outline.frag");
	// 创建场景shader
	Shader screenShader("screen.vert", "screen.frag");
	// 创建天空盒shader
	Shader skyShader("skybox.vert", "skybox.frag");
	// 创建带几何着色器的点shader
	Shader pointsShader("geometric.vert", "geometric.geom", "geometric.frag");

	// 顶点模型对象们
	VertexModels vertexModels;

	// 加载贴图
	TextureLoader textureLoader;
	unsigned int cubeTexture = textureLoader.loadTexture("texture/container2.png");
	unsigned int planeTexture = textureLoader.loadTexture("texture/wall.jpg");
	unsigned int grassTexture = textureLoader.loadTexture("texture/grass.png", true);
	vector<std::string> faces
	{
		"texture/skybox/right.jpg",
		"texture/skybox/left.jpg",
		"texture/skybox/top.jpg",
		"texture/skybox/bottom.jpg",
		"texture/skybox/front.jpg",
		"texture/skybox/back.jpg"
	};
	unsigned int skyTexture = textureLoader.loadSkyBox(faces);

	Model nanosuit("model/nanosuit/nanosuit.obj");

	// 创建帧缓冲
	FrameBuffer frameBuff(READ_ADN_DRAW, SCR_WIDTH, SCR_HEIGHT, true, true, true);
	frameBuff.Bind();

	shader.Use();
	shader.setInt("texture1", 0);

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

		frameBuff.Bind();

		// 启用深度测试，解决绘制物体穿模问题,这个实际只需要执行一次就可以了，只有在不断切换开启和关闭状态时才需要不断变换
		glEnable(GL_DEPTH_TEST);

		// 清屏
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// 通常颜色是需要每帧清除的，深度和模板只有在开启的时候才需要每帧清除
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 启用混合
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// 启用面剔除
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_FRONT);

		// 渲染
		// 创建模型矩阵
		glm::mat4 model;

		// 创建观察矩阵(摄像机)
		glm::mat4 view = camera.getViewMatrix();

		// 创建投影矩阵
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		
		// 使用着色器
		shader.Use();
		shader.setMatrix4("view", glm::value_ptr(view));
		shader.setMatrix4("projection", glm::value_ptr(projection));

		// 绘制纳米人
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyTexture);
		shader.setFloat("time", glfwGetTime());
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		shader.setMatrix4("model", glm::value_ptr(model));
		nanosuit.Draw(shader);

		// 绘制箱子
		//glBindTexture(GL_TEXTURE_CUBE_MAP, skyTexture);
		//glBindTexture(GL_TEXTURE_2D, cubeTexture);
		//vertexModels.DrawBoxes(shader);

		// 使用顶点模型shader
		//vertexModelShader.Use();
		//vertexModelShader.setMatrix4("view", glm::value_ptr(view));
		//vertexModelShader.setMatrix4("projection", glm::value_ptr(projection));

		// 绘制地板
		//glBindTexture(GL_TEXTURE_2D, planeTexture);
		//vertexModels.DrawPlane(vertexModelShader);

		// 绘制草
		//glBindTexture(GL_TEXTURE_2D, grassTexture);
		//vertexModels.DrawGrass(vertexModelShader);

		// 绘制背景（天空盒），最后绘制是因为我们修改了shader的深度
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_LEQUAL);
		skyShader.Use();
		glm::mat4 skeyView = glm::mat4(glm::mat3(camera.getViewMatrix()));
		skyShader.setMatrix4("view", glm::value_ptr(skeyView));
		skyShader.setMatrix4("projection", glm::value_ptr(projection));
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTexture);
		vertexModels.DrawSkyBox(skyShader);
		glDepthMask(GL_TRUE);

		// 绘制顶点
		//pointsShader.Use();
		//vertexModels.DrawPoints(pointsShader);

		frameBuff.Unbind();

		// 清除颜色
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		screenShader.Use();
		glDisable(GL_DEPTH_TEST);
		glBindTexture(GL_TEXTURE_2D, frameBuff.getTexture());
		vertexModels.DrawScreen(screenShader);

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