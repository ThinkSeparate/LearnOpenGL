//----������Ҫ���ⲿ���ļ�
#include <glad/glad.h>	// ��������OpenGL����ָ��
#include <GLFW/glfw3.h>	// glfw3��������OpenGL�Ŀ�ʹ��
#include <stb-master\stb_image.h> // ͼƬ���ؿ�

#include <glm/glm.hpp>	// ����OpenGL�任��صĿ��ļ���glm��OpenGL Mathematics����д
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

//----����ϵͳ���ļ�
#include <iostream>
#include <string>

//----�����Զ�����
#include "FrameBuffer.h"
#include "Camera.h"	// �����������
#include "Shader.h"	// ����shader��
#include "Model.h"
#include "SkyBox.h"
#include "TechnologyTest.h"	// �Զ���ļ��������ࣺѧϰ����Ҫʹ�úܶ��¼����������Դ�������������ʵ��

//----��������
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//----��������
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int loadTexture(const char* path);

//----����ȫ�ֱ���
// �����
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
// ������������ƫ��������ʼֵ����Ϊ��Ļ����
float lastX = SCR_WIDTH/2.0f, lastY = SCR_HEIGHT/2.0f;
// ����һ�����������������һ�ν��봰�ڣ�ƫ���������������
bool firstMouse = true;

// �����������������ÿ֡ʱ������
float deltaTime = 0.0f; // ��ǰ֡����һ֡��ʱ���
float lastFrame = 0.0f; // ��һ֡��ʱ��

int main() {

	// ��ʼ��GLFW
	glfwInit();
	// ʹ��opengl3.3�汾
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// ʹ�ú���ģʽ
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ����һ��800x600�Ĵ��ڣ����ڱ���ΪLearnOpenGL
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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

	float cubeVertices[] = {
		// Back face
	   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
	   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
	   // Front face
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
	   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
	   // Left face
	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
	   -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
	   // Right face
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
	   // Bottom face
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
	   // Top face
	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
	   -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left        
	};

	float planeVertices[] = {
		// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
	};

	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
	 // positions   // texCoords
		 -1.0f,  1.0f,  0.0f, 1.0f,
		 -1.0f, -1.0f,  0.0f, 0.0f,
		  1.0f, -1.0f,  1.0f, 0.0f,

		 -1.0f,  1.0f,  0.0f, 1.0f,
		  1.0f, -1.0f,  1.0f, 0.0f,
		  1.0f,  1.0f,  1.0f, 1.0f
	};

	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	vector<glm::vec3> vegetation;
	vegetation.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
	vegetation.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
	vegetation.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
	vegetation.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
	vegetation.push_back(glm::vec3(0.5f, 0.0f, -0.6f));
	
	// ����shader����
	Shader shader("model.vert", "model.frag");
	// ��������shader
	Shader outlineShader("outline.vert", "outline.frag");
	// ��������shader
	Shader screenShader("screen.vert", "screen.frag");
	// ������պ�shader
	Shader skyShader("skybox.vert", "skybox.frag");

	// ����VAO
	unsigned int cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// ��VAO
	unsigned int vegetationVAO;
	glGenVertexArrays(1, &vegetationVAO);
	glBindVertexArray(vegetationVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// �װ�VAO
	unsigned int planeVAO, planeVBO;
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// ����VAO
	unsigned int screenVAO, screenVBO;
	glGenVertexArrays(1, &screenVAO);
	glGenBuffers(1, &screenVBO);
	glBindVertexArray(screenVAO);
	glBindBuffer(GL_ARRAY_BUFFER, screenVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// ��պ�VAO
	unsigned int skyVAO, skyVBO;
	glGenVertexArrays(1, &skyVAO);
	glGenBuffers(1, &skyVBO);
	glBindVertexArray(skyVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// ������ͼ
	unsigned int cubeTexture = loadTexture("texture/container2.png");
	unsigned int planeTexture = loadTexture("texture/wall.jpg");
	unsigned int grassTexture = loadTexture("texture/grass.png");
	vector<std::string> faces
	{
		"texture/skybox/right.jpg",
		"texture/skybox/left.jpg",
		"texture/skybox/top.jpg",
		"texture/skybox/bottom.jpg",
		"texture/skybox/front.jpg",
		"texture/skybox/back.jpg"
	};
	SkyBox skybox(faces);
	unsigned int skyTexture = skybox.getTexture();

	// ����֡����
	FrameBuffer frameBuff(READ_ADN_DRAW, SCR_WIDTH, SCR_HEIGHT, true, true, true);
	frameBuff.Bind();

	shader.Use();
	shader.setInt("texture1", 0);

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

		frameBuff.Bind();

		// ������Ȳ��ԣ�����������崩ģ����,���ʵ��ֻ��Ҫִ��һ�ξͿ����ˣ�ֻ���ڲ����л������͹ر�״̬ʱ����Ҫ���ϱ任
		glEnable(GL_DEPTH_TEST);

		// ����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// ͨ����ɫ����Ҫÿ֡����ģ���Ⱥ�ģ��ֻ���ڿ�����ʱ�����Ҫÿ֡���
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// ���û��
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// �������޳�
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_FRONT);

		// ��Ⱦ
		// ����ģ�;���
		glm::mat4 model;

		// �����۲����(�����)
		glm::mat4 view = camera.getViewMatrix();

		// ����ͶӰ����
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		
		// ʹ����ɫ��
		shader.Use();
		shader.setMatrix4("view", glm::value_ptr(view));
		shader.setMatrix4("projection", glm::value_ptr(projection));

		// ���Ƶذ�
		glBindVertexArray(planeVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, planeTexture);
		model = glm::mat4(1.0f);
		shader.setMatrix4("model", glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// ��������
		glBindVertexArray(cubeVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, cubeTexture);
		for (unsigned int i = 0; i < vegetation.size(); i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, vegetation[i]);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.01f));
			shader.setMatrix4("model", glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// ���Ʋ�
		glBindVertexArray(vegetationVAO);
		glBindTexture(GL_TEXTURE_2D, grassTexture);
		for (unsigned int i = 0; i < vegetation.size(); i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, vegetation[i]);
			shader.setMatrix4("model", glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		// ���Ʊ�������պУ�������������Ϊ�����޸���shader�����
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_LEQUAL);
		skyShader.Use();
		glm::mat4 skeyView = glm::mat4(glm::mat3(camera.getViewMatrix()));
		skyShader.setMatrix4("view", glm::value_ptr(skeyView));
		skyShader.setMatrix4("projection", glm::value_ptr(projection));
		glBindVertexArray(skyVAO);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthMask(GL_TRUE);

		frameBuff.Unbind();

		// �����ɫ
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		screenShader.Use();
		glBindVertexArray(screenVAO);
		glDisable(GL_DEPTH_TEST);
		glBindTexture(GL_TEXTURE_2D, frameBuff.getTexture());
		glDrawArrays(GL_TRIANGLES, 0, 6);

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

unsigned int loadTexture(const char* path)
{
	// �����������
	unsigned int textureID;
	glGenTextures(1, &textureID);

	// ����ͼƬ
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

	if (data) {
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		// ������
		glBindTexture(GL_TEXTURE_2D, textureID);

		// ��������
		// ������Ŀ�꣬�����伶�𣬴洢��ʽ�������ȣ�����߶ȣ�0��Դ���ݸ�ʽ��Դ�������ͣ� ͼ�����ݣ�
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		// ���ɶ༶��������
		glGenerateMipmap(GL_TEXTURE_2D);

		// Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	// �ͷ�ͼ���ڴ�
	stbi_image_free(data);

	return textureID;
}