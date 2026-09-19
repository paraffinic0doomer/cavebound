#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glm/glm.hpp>

// Look-at camera that also works as a free-fly camera. It produces the view and projection matrices;
// reading the keyboard and mouse is done by CameraController.
//
// Orientation is stored as two angles, in degrees:
//   yaw    turn around the vertical axis (0 = looking along +X, 90 = looking along +Z)
//   pitch  look up (+) or down (-), limited to +-89 so the camera never flips over
class Camera {
public:
	glm::vec3 position;
	glm::vec3 target;   // always position + front, kept in sync by the functions below
	glm::vec3 up;

	float fov;         // vertical field of view, in degrees
	float aspectRatio; // width / height
	float nearPlane;
	float farPlane;

	float yaw;
	float pitch;

	Camera(glm::vec3 position, glm::vec3 target, float aspectRatio,
		float fov = 45.0f, float nearPlane = 0.1f, float farPlane = 100.0f);

	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;

	// Puts the camera at newPosition, looking at lookTarget
	void LookFrom(const glm::vec3& newPosition, const glm::vec3& lookTarget);

	void SetAngles(float newYaw, float newPitch);
	void Rotate(float deltaYaw, float deltaPitch);
	void Translate(const glm::vec3& offset); // moves position and target together

	glm::vec3 GetFront() const; // unit vector the camera looks along
	glm::vec3 GetRight() const; // unit vector pointing to the camera's right
};

#endif
