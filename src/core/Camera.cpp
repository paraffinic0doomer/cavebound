#include "Camera.h"

#include <algorithm>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

namespace {
// Direction from yaw and pitch (degrees): yaw turns in the XZ plane, pitch tilts up or down
glm::vec3 FrontFromAngles(float yawDegrees, float pitchDegrees) {
	float yaw = glm::radians(yawDegrees);
	float pitch = glm::radians(pitchDegrees);
	return glm::vec3(std::cos(pitch) * std::cos(yaw), std::sin(pitch), std::cos(pitch) * std::sin(yaw));
}
}

Camera::Camera(glm::vec3 position, glm::vec3 target, float aspectRatio,
	float fov, float nearPlane, float farPlane)
	: position(position), target(target), up(0.0f, 1.0f, 0.0f),
	  fov(fov), aspectRatio(aspectRatio), nearPlane(nearPlane), farPlane(farPlane),
	  yaw(0.0f), pitch(0.0f) {
	LookFrom(position, target);
}

// World space -> camera space
glm::mat4 Camera::GetViewMatrix() const {
	return glm::lookAt(position, target, up);
}

// Camera space -> clip space (perspective: distant objects look smaller)
glm::mat4 Camera::GetProjectionMatrix() const {
	return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

void Camera::LookFrom(const glm::vec3& newPosition, const glm::vec3& lookTarget) {
	position = newPosition;

	glm::vec3 direction = glm::normalize(lookTarget - newPosition);
	yaw = glm::degrees(std::atan2(direction.z, direction.x));
	pitch = glm::degrees(std::asin(std::clamp(direction.y, -1.0f, 1.0f)));

	SetAngles(yaw, pitch);
}

void Camera::SetAngles(float newYaw, float newPitch) {
	yaw = newYaw;
	pitch = std::clamp(newPitch, -89.0f, 89.0f);
	target = position + FrontFromAngles(yaw, pitch);
}

void Camera::Rotate(float deltaYaw, float deltaPitch) {
	SetAngles(yaw + deltaYaw, pitch + deltaPitch);
}

void Camera::Translate(const glm::vec3& offset) {
	position += offset;
	target += offset;
}

glm::vec3 Camera::GetFront() const {
	return FrontFromAngles(yaw, pitch);
}

glm::vec3 Camera::GetRight() const {
	return glm::normalize(glm::cross(GetFront(), up));
}
