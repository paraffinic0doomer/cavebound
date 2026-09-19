#ifndef DEMO_VIEWS_CLASS_H
#define DEMO_VIEWS_CLASS_H

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "core/CameraController.h"
#include "cave/CaveLayout.h"
#include "gameobjects/LevelObjects.h"
#include "robot/Robot.h"

// Number keys that glide the camera to a close-up of one kind of object, for showing the scene to someone.
// Pressing the same key again moves on to the next object of that kind (next coin, next gem, ...).
//
//   0  overview of the whole cave      5  rare checkpoint
//   1  treasure chest                  6  exit marker
//   2  coins                           7  robot
//   3  gems                            8  cave entrance
//   4  normal checkpoints              9  inside the main chamber (pillars, rocks, stalactites)
class DemoViews {
public:
	DemoViews(CameraController& controller, const CaveLayout& layout, LevelObjects& level, Robot& robot);

	// Call once per frame: starts a glide when one of the number keys is pressed
	void Update();

	// The starting view (key 0)
	static glm::vec3 OverviewPosition();
	static glm::vec3 OverviewTarget();

	// Prints the key list to the console
	static void PrintHelp();

private:
	struct View {
		glm::vec3 position; // where the camera goes
		glm::vec3 target;   // what it looks at
	};

	struct Group {
		int key;                // GLFW_KEY_*
		std::string name;
		std::vector<View> views;
		size_t next;            // index of the view the next key press flies to
	};

	CameraController& controller;
	std::vector<Group> groups;

	// One view per object: the camera sits at `direction` from the object (x = to its right, y = up, z = in
	// front of it, turned with the object's own rotation) looking at a point `lookHeight` up its middle.
	// lookHeight and distance are for an object at scale 1 and are multiplied by the object's scale.
	void AddObjectGroup(int key, const std::string& name, const std::vector<const CompositeObject*>& objects,
		float lookHeight, float distance, const glm::vec3& direction = glm::vec3(0.5f, 0.6f, 1.0f));
};

#endif
