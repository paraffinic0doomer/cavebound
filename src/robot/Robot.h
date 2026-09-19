#ifndef ROBOT_CLASS_H
#define ROBOT_CLASS_H

#include <glm/glm.hpp>

#include "primitives/CompositeObject.h"

// Static Phase 3 exploration robot. The Robot is the root of its own hierarchy:
//
// Robot
//  |- Body
//  |- Head
//  |    |- Eyes
//  |    '- Antenna
//  |- Left arm / Right arm
//  |- Left wheel / Right wheel
//  '- Flashlight
//
// Changing the Robot transform moves every child. SetHeadRotation only changes the
// head branch, so its eyes and antenna follow while the body, wheels and arms do not.
class Robot : public CompositeObject {
public:
	Robot();

	// Explicit robot-level controls for later phases. They only set transforms; no movement is implemented here.
	void Draw(Shader& shader);
	void SetPosition(const glm::vec3& newPosition);
	void SetRotation(const glm::vec3& newRotation);
	void SetScale(const glm::vec3& newScale);
	void SetHeadRotation(const glm::vec3& newRotation);

	glm::vec3 GetHeadRotation() const;

private:
	CompositeObject* head;

	void BuildBody();
	void BuildHead();
	void BuildArm(float side, const char* name);
	void BuildWheel(float side, const char* name);
	void BuildFlashlight();
};

#endif
