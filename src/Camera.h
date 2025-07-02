#pragma once

#include <glm/gtc/type_ptr.hpp>

struct GLFWwindow;

class Camera
{
public:
	Camera(int _screenW, int _screenH);

	void Start(GLFWwindow* _window);
	void Update();

	glm::mat4x4 GetViewMatrix();
	glm::mat4x4 GetProjMatrix();

private:
	void HandleKeyboard(int keyCode);
	void HandleMouse(float xpos, float ypos);
	void HandleScroll(double xoffset, double yoffset);

	int screenW, screenH;
	float lastX {0};
	float lastY {0};

	float yaw {-90};
	float pitch {0};
	float fov {45.0f};

	glm::vec3 cameraPos {glm::vec3(0.0f, 0.0f, 3.0f)};
	glm::vec3 cameraFront {glm::vec3(0.0f, 0.0f, -1.0f)};
	glm::vec3 cameraUp {glm::vec3(0.0f, 1.0f, 0.0f)};

	GLFWwindow* window {nullptr};
};

