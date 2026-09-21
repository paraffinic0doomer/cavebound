#ifndef CAMERA_CONTROLLER_CLASS_H
#define CAMERA_CONTROLLER_CLASS_H

#include <glm/glm.hpp>

struct GLFWwindow;
class Camera;

// Moves a Camera from the keyboard and mouse, and can glide it to a chosen view.
//
//   W / S        forward / back           A / D    left / right
//   E / Q        up / down                Shift    move 3x faster
//   hold the right mouse button and drag to look around (arrow keys also turn the camera)
//   mouse wheel  change the movement speed
//
// Moving, looking, or pressing a movement key while the camera is gliding cancels the glide.
class CameraController {
public:
	CameraController(GLFWwindow* window, Camera& camera);

	// Call once per frame with the time since the last frame, in seconds
	void Update(float deltaTime);
	void UpdateThirdPerson(float deltaTime, glm::vec3& robotPosition, glm::vec3& robotRotation);

	// Smoothly moves the camera to `position`, looking at `lookTarget`
	void FlyTo(const glm::vec3& position, const glm::vec3& lookTarget, float seconds = 0.9f);

	// True exactly once each time `key` (a GLFW_KEY_* value) goes down.
	// Call it every frame for every key you care about.
	bool KeyPressed(int key);

private:
	GLFWwindow* window;
	Camera& camera;

	float moveSpeed;        // units per second
	float lookSensitivity;  // degrees per pixel of mouse movement
	float thirdPersonPitch;

	bool mouseLooking;
	double lastMouseX, lastMouseY;

	// Glide state
	bool flying;
	float flightTime, flightDuration;
	glm::vec3 startPosition, endPosition;
	float startYaw, endYaw, startPitch, endPitch;

	bool keyWasDown[512];

	bool KeyDown(int key) const;
	void UpdateGlide(float deltaTime);
};

#endif
