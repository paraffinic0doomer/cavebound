#include "CameraController.h"

#include <algorithm>
#include <cmath>
#include <GLFW/glfw3.h>

#include "Camera.h"

namespace {
double scrollAccumulated = 0.0; // filled by the GLFW scroll callback, used up in Update

void ScrollCallback(GLFWwindow*, double, double yOffset) {
	scrollAccumulated += yOffset;
}
}

CameraController::CameraController(GLFWwindow* window, Camera& camera)
	: window(window), camera(camera),
	  moveSpeed(6.0f), lookSensitivity(0.15f),
	  thirdPersonPitch(-24.0f),
	  mouseLooking(false), lastMouseX(0.0), lastMouseY(0.0),
	  flying(false), flightTime(0.0f), flightDuration(1.0f),
	  startPosition(0.0f), endPosition(0.0f), startYaw(0.0f), endYaw(0.0f), startPitch(0.0f), endPitch(0.0f) {
	std::fill(std::begin(keyWasDown), std::end(keyWasDown), false);
	glfwSetScrollCallback(window, ScrollCallback);
}

void CameraController::UpdateThirdPerson(float deltaTime, glm::vec3& robotPosition, glm::vec3& robotRotation) {
	float lookYaw = 0.0f;
	float lookPitch = 0.0f;
	bool rightButton = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
	if (rightButton) {
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		if (mouseLooking) {
			lookYaw = static_cast<float>(x - lastMouseX) * lookSensitivity;
			lookPitch = static_cast<float>(y - lastMouseY) * lookSensitivity;
		}
		lastMouseX = x;
		lastMouseY = y;
	}
	mouseLooking = rightButton;

	float heading = camera.yaw + lookYaw;
	if (lookYaw != 0.0f || lookPitch != 0.0f)
		thirdPersonPitch = std::clamp(thirdPersonPitch + lookPitch, -8.0f, 55.0f);

	glm::vec3 forward(std::cos(glm::radians(heading)), 0.0f, std::sin(glm::radians(heading)));
	glm::vec3 right(-forward.z, 0.0f, forward.x);
	glm::vec3 move(0.0f);
	if (KeyDown(GLFW_KEY_W)) move += forward;
	if (KeyDown(GLFW_KEY_S)) move -= forward;
	if (KeyDown(GLFW_KEY_D)) move += right;
	if (KeyDown(GLFW_KEY_A)) move -= right;
	if (glm::length(move) > 0.0f) {
		float speed = (KeyDown(GLFW_KEY_LEFT_SHIFT) || KeyDown(GLFW_KEY_RIGHT_SHIFT)) ? 7.0f : 3.5f;
		robotPosition += glm::normalize(move) * speed * deltaTime;
		robotRotation.y = glm::degrees(std::atan2(move.z, move.x));
	}

	float verticalOffset = -std::tan(glm::radians(thirdPersonPitch)) * 9.0f;
	glm::vec3 cameraPosition = robotPosition - forward * 9.0f + glm::vec3(0.0f, 1.5f + verticalOffset, 0.0f);
	camera.LookFrom(cameraPosition, robotPosition + glm::vec3(0.0f, 1.5f, 0.0f));
}

bool CameraController::KeyDown(int key) const {
	return glfwGetKey(window, key) == GLFW_PRESS;
}

bool CameraController::KeyPressed(int key) {
	bool down = KeyDown(key);
	bool pressed = down && !keyWasDown[key];
	keyWasDown[key] = down;
	return pressed;
}

void CameraController::FlyTo(const glm::vec3& position, const glm::vec3& lookTarget, float seconds) {
	// Work out the end angles by pointing a copy of the camera at the target
	Camera destination = camera;
	destination.LookFrom(position, lookTarget);

	startPosition = camera.position;
	endPosition = position;
	startYaw = camera.yaw;
	startPitch = camera.pitch;

	// Turn the short way round: bring the yaw difference into [-180, 180]
	float delta = std::fmod(destination.yaw - camera.yaw + 540.0f, 360.0f) - 180.0f;
	endYaw = startYaw + delta;
	endPitch = destination.pitch;

	flightTime = 0.0f;
	flightDuration = std::max(seconds, 0.01f);
	flying = true;
}

void CameraController::UpdateGlide(float deltaTime) {
	flightTime += deltaTime;
	float t = std::min(flightTime / flightDuration, 1.0f);
	float eased = t * t * (3.0f - 2.0f * t); // smoothstep: slow start, slow finish

	camera.position = startPosition + (endPosition - startPosition) * eased;
	camera.SetAngles(startYaw + (endYaw - startYaw) * eased, startPitch + (endPitch - startPitch) * eased);

	if (t >= 1.0f) {
		flying = false;
	}
}

void CameraController::Update(float deltaTime) {
	// Mouse wheel: every notch changes the speed by 20%
	if (scrollAccumulated != 0.0) {
		moveSpeed = std::clamp(moveSpeed * std::pow(1.2f, static_cast<float>(scrollAccumulated)), 0.5f, 40.0f);
		scrollAccumulated = 0.0;
	}

	// Mouse look while the right button is held
	float lookYaw = 0.0f, lookPitch = 0.0f;
	bool rightButton = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
	if (rightButton) {
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		if (mouseLooking) {
			lookYaw += static_cast<float>(x - lastMouseX) * lookSensitivity;
			lookPitch -= static_cast<float>(y - lastMouseY) * lookSensitivity; // mouse down = look down
		}
		lastMouseX = x;
		lastMouseY = y;
	}
	mouseLooking = rightButton;

	// Arrow keys turn the camera too
	const float turnSpeed = 80.0f; // degrees per second
	if (KeyDown(GLFW_KEY_LEFT))  lookYaw -= turnSpeed * deltaTime;
	if (KeyDown(GLFW_KEY_RIGHT)) lookYaw += turnSpeed * deltaTime;
	if (KeyDown(GLFW_KEY_UP))    lookPitch += turnSpeed * deltaTime;
	if (KeyDown(GLFW_KEY_DOWN))  lookPitch -= turnSpeed * deltaTime;

	// Movement keys, relative to where the camera looks
	glm::vec3 move(0.0f);
	if (KeyDown(GLFW_KEY_W)) move += camera.GetFront();
	if (KeyDown(GLFW_KEY_S)) move -= camera.GetFront();
	if (KeyDown(GLFW_KEY_D)) move += camera.GetRight();
	if (KeyDown(GLFW_KEY_A)) move -= camera.GetRight();
	if (KeyDown(GLFW_KEY_E)) move += camera.up;
	if (KeyDown(GLFW_KEY_Q)) move -= camera.up;

	bool userInput = lookYaw != 0.0f || lookPitch != 0.0f || glm::length(move) > 0.0f;

	if (flying) {
		if (!userInput) {
			UpdateGlide(deltaTime);
			return;
		}
		flying = false; // the user took over
	}

	if (lookYaw != 0.0f || lookPitch != 0.0f) {
		camera.Rotate(lookYaw, lookPitch);
	}
	if (glm::length(move) > 0.0f) {
		bool fast = KeyDown(GLFW_KEY_LEFT_SHIFT) || KeyDown(GLFW_KEY_RIGHT_SHIFT);
		float distance = moveSpeed * (fast ? 3.0f : 1.0f) * deltaTime;
		camera.Translate(glm::normalize(move) * distance);
	}
}
