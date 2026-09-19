#ifndef GAME_OBJECT_CLASS_H
#define GAME_OBJECT_CLASS_H

#include <string>
#include <glm/glm.hpp>

#include "primitives/CompositeObject.h"

// Base class of the Phase 4 objects (Treasure, Coin, Gem, Checkpoint, ExitMarker).
// Every game object is built from primitives around its own origin, which sits on the floor, in the
// middle of the object. It supports the same controls as the Robot:
//
//   position   where it stands (world units)
//   rotation   Euler angles in degrees (rotation.y turns it around the vertical axis)
//   scale      size multiplier
//   Draw()     draws the object and all of its parts
//
// Objects are static: nothing here moves, spins or reacts to the robot.
class GameObject : public CompositeObject {
public:
	explicit GameObject(std::string name);

	void Draw(Shader& shader);

	void SetPosition(const glm::vec3& newPosition);
	void SetRotation(const glm::vec3& newRotation);
	void SetScale(const glm::vec3& newScale);
	void SetScale(float uniformScale);
};

#endif
