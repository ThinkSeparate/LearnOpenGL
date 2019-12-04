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
#include "VertexModels.h"
#include "TextureLoader.h"
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
	
	// ����shader����
	Shader shader("model.vert", "model.geom", "model.frag");
	// ���ɶ���ģ��shader
	Shader vertexModelShader("vertex.vert", "vertex.frag");
	// ��������shader
	Shader outlineShader("outline.vert", "outline.frag");
	// ��������shader
	Shader screenShader("screen.vert", "screen.frag");
	// ������պ�shader
	Shader skyShader("skybox.vert", "skybox.frag");
	// ������������ɫ���ĵ�shader
	Shader pointsShader("geometric.vert", "geometric.geom", "geometric.frag");

	// ����ģ�Ͷ�����
	VertexModels vertexModels;

	// ������ͼ
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

		// ����������
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyTexture);
		shader.setFloat("time", glfwGetTime());
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		shader.setMatrix4("model", glm::value_ptr(model));
		nanosuit.Draw(shader);

		// ��������
		//glBindTexture(GL_TEXTURE_CUBE_MAP, skyTexture);
		//glBindTexture(GL_TEXTURE_2D, cubeTexture);
		//vertexModels.DrawBoxes(shader);

		// ʹ�ö���ģ��shader
		//vertexModelShader.Use();
		//vertexModelShader.setMatrix4("view", glm::value_ptr(view));
		//vertexModelShader.setMatrix4("projection", glm::value_ptr(projection));

		// ���Ƶذ�
		//glBindTexture(GL_TEXTURE_2D, planeTexture);
		//vertexModels.DrawPlane(vertexModelShader);

		// ���Ʋ�
		//glBindTexture(GL_TEXTURE_2D, grassTexture);
		//vertexModels.DrawGrass(vertexModelShader);

		// ���Ʊ�������պУ�������������Ϊ�����޸���shader�����
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_LEQUAL);
		skyShader.Use();
		glm::mat4 skeyView = glm::mat4(glm::mat3(camera.getViewMatrix()));
		skyShader.setMatrix4("view", glm::value_ptr(skeyView));
		skyShader.setMatrix4("projection", glm::value_ptr(projection));
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTexture);
		vertexModels.DrawSkyBox(skyShader);
		glDepthMask(GL_TRUE);

		// ���ƶ���
		//pointsShader.Use();
		//vertexModels.DrawPoints(pointsShader);

		frameBuff.Unbind();

		// �����ɫ
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		screenShader.Use();
		glDisable(GL_DEPTH_TEST);
		glBindTexture(GL_TEXTURE_2D, frameBuff.getTexture());
		vertexModels.DrawScreen(screenShader);

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