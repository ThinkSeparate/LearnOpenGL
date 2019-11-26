#pragma once

#include <GLFW/glfw3.h>	// glfw3，包含了OpenGL的库使用
#include <glm/glm.hpp>	// 引用OpenGL变换相关的库文件，glm是OpenGL Mathematics的缩写
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	Camera(glm::vec3 positon = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
	// 可以获得观察矩阵
	float getZoom();
	glm::vec3 getPosition();
	glm::vec3 getFront();
	// 可以获得观察矩阵
	glm::mat4 getViewMatrix();
	// 键盘控制
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	//鼠标控制
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	// 滚轮控制
	void ProcessMouseScroll(float yoffset);
private:
	// 摄像机的世界位置，和世界向上向量
	glm::vec3 position;
	glm::vec3 world_up;
	// 摄像机的三个向量
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 front;
	// 摄像机的三个欧拉角
	float yaw;
	float pitch;
	float roll;
	// 摄像机的移速，鼠标灵敏度，滚动缩放
	float speed;
	float sensitivity;
	float zoom;
	// 提供摄像机更好函数（重新计算摄像机方向）
	void updateCameraVectors();
};

