//----������Ҫ���ⲿ���ļ�
#include <glad/glad.h>	// ��������OpenGL����ָ��
#include <GLFW/glfw3.h>	// glfw3��������OpenGL�Ŀ�ʹ��
#include <stb-master\stb_image.h> // ͼƬ���ؿ�
#include <glm/glm.hpp>	// ����OpenGL�任��صĿ��ļ���glm��OpenGL Mathematics����д
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

//----����ϵͳ���ļ�
#include <iostream>

//----�����Զ�����
#include "Camera.h"	// �����������
#include "Shader.h"	// ����shader��
#include "TechnologyTest.h"	// �Զ���ļ��������ࣺѧϰ����Ҫʹ�úܶ��¼����������Դ�������������ʵ��

//----��������
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//----��������
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

//----����ȫ�ֱ���
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
// �����������������ÿ֡ʱ������
float deltaTime = 0.0f; // ��ǰ֡����һ֡��ʱ���
float lastFrame = 0.0f; // ��һ֡��ʱ��
// ������������ƫ��������ʼֵ����Ϊ��Ļ����
float lastX = SCR_WIDTH/2.0f, lastY = SCR_HEIGHT/2.0f;
// ����һ�����������������һ�ν��봰�ڣ�ƫ���������������
bool firstMouse = true;

// ����Ƶ�λ��
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

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
	framebuffer_size_callback(window, SCR_WIDTH, SCR_HEIGHT);

	float vertices[] = {
		//	----λ��----		----������----
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	unsigned int indices[] = { // ע��������0��ʼ! 
		0, 1, 3, // ��һ��������
		1, 2, 3  // �ڶ���������
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

	// ����ǽ��ͼƬ
	int width, height, nrChannels;
	unsigned char* data1 = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);

	// �����������
	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);
	// ������
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	// Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (data1) {
		// ��������
		// ������Ŀ�꣬�����伶�𣬴洢��ʽ�������ȣ�����߶ȣ�0��Դ���ݸ�ʽ��Դ�������ͣ� ͼ�����ݣ�
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
		// ���ɶ༶��������
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	// ��תy��
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);

	glGenTextures(1, &texture2);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	// Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (data2) {
		// ��������
		// ������Ŀ�꣬�����伶�𣬴洢��ʽ�������ȣ�����߶ȣ�0��Դ���ݸ�ʽ��Դ�������ͣ� ͼ�����ݣ�
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		// ���ɶ༶��������
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	// �ͷ�ͼ���ڴ�
	stbi_image_free(data1);
	stbi_image_free(data2);

	Shader shader("vertex.glsl", "fragment.glsl");
	Shader lightShader("lightVertex.glsl", "lightFragment.glsl");

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	// �Զ�������λ��Ϊ�������ö�������(location = 0)����������Ĭ�Ͻ���
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(2);

	//	�����ƹ�VAO
	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	// ֻ��Ҫ��VBO�����ٴ�����VBO�����ݣ���Ϊ���ӵ�VBO�������Ѿ���������ȷ�������嶥������
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	// ���õ�������Ķ�������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// ��������
	TechnologyTest technologyTest;
	technologyTest.TestAll();

	// ��ÿ��ѭ����Ⱦ֮ǰ����Ƿ���Ҫ�˳�
	while (!glfwWindowShouldClose(window))
	{
		// ���µ�ǰ֡ʱ��
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// ����
		processInput(window);

		// ������Ȳ��ԣ�����������崩ģ����,���ʵ��ֻ��Ҫִ��һ�ξͿ����ˣ�ֻ���ڲ����л������͹ر�״̬ʱ����Ҫ���ϱ任
		glEnable(GL_DEPTH_TEST);

		// ����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// �����Ȼ�����ÿһ֡��Ҫִ�еģ������ϣ��������ȷ
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// ��Ⱦ
		// �����۲����(�����)
		glm::mat4 view = camera.getViewMatrix();

		// ����ͶӰ����
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		// ����Ƶ�λ��
		glm::mat4 model;
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));

		// ʹ�õ���ɫ��
		lightShader.Use();
		lightShader.setMatrix4("view", glm::value_ptr(view));
		lightShader.setMatrix4("projection", glm::value_ptr(projection));
		lightShader.setMatrix4("model", glm::value_ptr(model));

		// ���Ƶ�
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ʹ����ɫ��
		shader.Use();
		shader.setFloat("objectColor", 1.0f, 0.5f, 0.31f);
		shader.setFloat("lightColor", 1.0f, 1.0f, 1.0f);
		shader.setFloat("lightPos", lightPos);
		shader.setFloat("viewPos", camera.getPosition());
		// ����������
		shader.setInt("ourTexture1", 0);
		shader.setInt("ourTexture2", 1);

		// �������붥����ɫ�������㶥������
		shader.setMatrix4("view", glm::value_ptr(view));
		shader.setMatrix4("projection", glm::value_ptr(projection));
		model = glm::mat4(1.0f);
		shader.setMatrix4("model", glm::value_ptr(model));

		// �󶨶�������
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	
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
	// ���ع�겢��׽��������㷢����겻���ˣ�
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	// ����������
	glfwSetCursorPosCallback(window, mouse_callback);

	// ���ּ���
	glfwSetScrollCallback(window, scroll_callback);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
	float cameraSpeed = 2.5f * deltaTime;
	// w������ǰ�ƶ�
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	// s��������ƶ�
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	// a���������ƶ�
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	// d���������ƶ�
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}

// ����¼�
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse) // ���bool������ʼʱ���趨Ϊtrue��
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	// ����ƫ����
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;	// ע���������෴�ģ���Ϊy�����Ǵӵײ����������������
	// ������һ�ε����λ��
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