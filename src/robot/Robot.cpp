#include "Robot.h"

#include <memory>

#include "primitives/Cone.h"
#include "primitives/Cube.h"
#include "primitives/Cylinder.h"
#include "primitives/Sphere.h"

namespace {
const glm::vec3 BODY_COLOR(0.18f, 0.28f, 0.34f);
const glm::vec3 TRIM_COLOR(0.34f, 0.48f, 0.53f);
const glm::vec3 DARK_METAL(0.10f, 0.13f, 0.15f);
const glm::vec3 WHEEL_COLOR(0.07f, 0.08f, 0.09f);
const glm::vec3 EYE_COLOR(0.34f, 0.88f, 0.90f);
const glm::vec3 LENS_COLOR(0.95f, 0.80f, 0.42f);
}

Robot::Robot() : CompositeObject("Robot"), head(nullptr) {
	BuildBody();
	BuildHead();
	BuildArm(-1.0f, "Left arm");
	BuildArm(1.0f, "Right arm");
	BuildWheel(-1.0f, "Left wheel");
	BuildWheel(1.0f, "Right wheel");
	BuildFlashlight();
}

void Robot::Draw(Shader& shader) {
	DrawOpaque(shader);
}

void Robot::SetPosition(const glm::vec3& newPosition) {
	position = newPosition;
}

void Robot::SetRotation(const glm::vec3& newRotation) {
	rotation = newRotation;
}

void Robot::SetScale(const glm::vec3& newScale) {
	scale = newScale;
}

void Robot::SetHeadRotation(const glm::vec3& newRotation) {
	if (head != nullptr) {
		head->rotation = newRotation;
	}
}

glm::vec3 Robot::GetHeadRotation() const {
	return head != nullptr ? head->rotation : glm::vec3(0.0f);
}

void Robot::BuildBody() {
	auto body = std::make_unique<CompositeObject>("Body");

	// Main chassis and a smaller front panel. Both are relative to the robot root.
	body->AddPart(std::make_unique<Cube>(1.0f, BODY_COLOR),
		glm::vec3(0.0f, 1.34f, 0.0f), glm::vec3(0.0f), glm::vec3(1.50f, 1.15f, 1.10f));
	body->AddPart(std::make_unique<Cube>(1.0f, TRIM_COLOR),
		glm::vec3(0.0f, 1.38f, 0.57f), glm::vec3(0.0f), glm::vec3(0.92f, 0.48f, 0.08f));
	body->AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 8, DARK_METAL),
		glm::vec3(0.0f, 1.94f, 0.0f), glm::vec3(0.0f), glm::vec3(0.46f, 0.18f, 0.46f));

	AddChild(std::move(body));
}

void Robot::BuildHead() {
	auto headObject = std::make_unique<CompositeObject>("Head");
	headObject->position = glm::vec3(0.0f, 2.38f, 0.0f);

	// Head shell and a dark face plate.
	headObject->AddPart(std::make_unique<Cube>(1.0f, TRIM_COLOR),
		glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.22f, 0.75f, 0.95f));
	headObject->AddPart(std::make_unique<Cube>(1.0f, DARK_METAL),
		glm::vec3(0.0f, 0.03f, 0.49f), glm::vec3(0.0f), glm::vec3(0.98f, 0.42f, 0.06f));

	// Eyes are a child of Head, not independent world objects.
	auto eyes = std::make_unique<CompositeObject>("Eyes");
	eyes->position = glm::vec3(0.0f, 0.05f, 0.54f);
	eyes->AddPart(std::make_unique<Sphere>(0.5f, 8, 5, EYE_COLOR),
		glm::vec3(-0.29f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.22f));
	eyes->AddPart(std::make_unique<Sphere>(0.5f, 8, 5, EYE_COLOR),
		glm::vec3(0.29f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.22f));
	headObject->AddChild(std::move(eyes));

	// Antenna is also under Head: a low-poly mast and a small receiver tip.
	auto antenna = std::make_unique<CompositeObject>("Antenna");
	antenna->position = glm::vec3(0.0f, 0.38f, 0.0f);
	antenna->AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 7, DARK_METAL),
		glm::vec3(0.0f, 0.24f, 0.0f), glm::vec3(0.0f), glm::vec3(0.12f, 0.48f, 0.12f));
	antenna->AddPart(std::make_unique<Sphere>(0.5f, 7, 4, EYE_COLOR),
		glm::vec3(0.0f, 0.54f, 0.0f), glm::vec3(0.0f), glm::vec3(0.22f));
	headObject->AddChild(std::move(antenna));

	head = &AddChild(std::move(headObject));
}

void Robot::BuildArm(float side, const char* name) {
	auto arm = std::make_unique<CompositeObject>(name);
	arm->position = glm::vec3(side * 1.02f, 1.50f, 0.0f);
	arm->rotation = glm::vec3(0.0f, 0.0f, side * -14.0f);

	arm->AddPart(std::make_unique<Sphere>(0.5f, 7, 4, TRIM_COLOR),
		glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.42f));
	arm->AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 7, BODY_COLOR),
		glm::vec3(0.0f, -0.42f, 0.0f), glm::vec3(0.0f), glm::vec3(0.34f, 0.82f, 0.34f));
	arm->AddPart(std::make_unique<Sphere>(0.5f, 7, 4, DARK_METAL),
		glm::vec3(0.0f, -0.86f, 0.06f), glm::vec3(0.0f), glm::vec3(0.42f, 0.34f, 0.38f));

	AddChild(std::move(arm));
}

void Robot::BuildWheel(float side, const char* name) {
	auto wheel = std::make_unique<CompositeObject>(name);
	wheel->position = glm::vec3(side * 1.02f, 0.48f, 0.0f);

	// The cylinder is rotated around Z so its axle points through the robot's left/right sides.
	wheel->AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 10, WHEEL_COLOR),
		glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 90.0f), glm::vec3(0.92f, 0.42f, 0.92f));
	wheel->AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 8, TRIM_COLOR),
		glm::vec3(side * 0.23f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 90.0f), glm::vec3(0.44f, 0.08f, 0.44f));

	AddChild(std::move(wheel));
}

void Robot::BuildFlashlight() {
	auto flashlight = std::make_unique<CompositeObject>("Flashlight");
	flashlight->position = glm::vec3(0.0f, 1.36f, 0.56f);

	// This is the physical torch model only; it intentionally emits no OpenGL light in this phase.
	flashlight->AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 8, DARK_METAL),
		glm::vec3(0.0f, 0.0f, 0.27f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.34f, 0.70f, 0.34f));
	flashlight->AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 8, LENS_COLOR),
		glm::vec3(0.0f, 0.0f, 0.64f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.38f, 0.09f, 0.38f));
	flashlight->AddPart(std::make_unique<Cone>(0.5f, 1.0f, 7, TRIM_COLOR),
		glm::vec3(0.0f, 0.0f, -0.13f), glm::vec3(-90.0f, 0.0f, 0.0f), glm::vec3(0.43f, 0.24f, 0.43f));

	AddChild(std::move(flashlight));
}
