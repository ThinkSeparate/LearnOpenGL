#pragma once

#include <GLFW/glfw3.h>	// glfw3��������OpenGL�Ŀ�ʹ��
#include <glm/glm.hpp>	// ����OpenGL�任��صĿ��ļ���glm��OpenGL Mathematics����д
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
	// ���Ի�ù۲����
	float getZoom();
	glm::vec3 getPosition();
	glm::vec3 getFront();
	// ���Ի�ù۲����
	glm::mat4 getViewMatrix();
	// ���̿���
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	//������
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	// ���ֿ���
	void ProcessMouseScroll(float yoffset);
private:
	// �����������λ�ã���������������
	glm::vec3 position;
	glm::vec3 world_up;
	// ���������������
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 front;
	// �����������ŷ����
	float yaw;
	float pitch;
	float roll;
	// ����������٣���������ȣ���������
	float speed;
	float sensitivity;
	float zoom;
	// �ṩ��������ú��������¼������������
	void updateCameraVectors();
};

