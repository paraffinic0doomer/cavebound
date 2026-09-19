#include "DemoViews.h"

#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

DemoViews::DemoViews(CameraController& controller, const CaveLayout& layout, LevelObjects& level, Robot& robot)
	: controller(controller) {

	// 0: the whole cave
	groups.push_back({ GLFW_KEY_0, "Overview", { { OverviewPosition(), OverviewTarget() } }, 0 });

	// 1: chest
	std::vector<const CompositeObject*> chest;
	if (level.GetTreasure() != nullptr) chest.push_back(level.GetTreasure());
	// Seen from its right side: the coin lying in front of the chest would otherwise be in the way
	AddObjectGroup(GLFW_KEY_1, "Treasure chest", chest, 0.5f, 3.2f, glm::vec3(1.0f, 0.75f, 0.55f));

	// 2: coins
	AddObjectGroup(GLFW_KEY_2, "Coin", std::vector<const CompositeObject*>(level.GetCoins().begin(), level.GetCoins().end()), 0.45f, 2.2f);

	// 3: gems
	AddObjectGroup(GLFW_KEY_3, "Gem", std::vector<const CompositeObject*>(level.GetGems().begin(), level.GetGems().end()), 0.65f, 2.4f);

	// 4 and 5: the checkpoints, normal and rare
	std::vector<const CompositeObject*> normalCheckpoints, rareCheckpoints;
	for (const Checkpoint* checkpoint : level.GetCheckpoints()) {
		(checkpoint->GetType() == CheckpointType::Rare ? rareCheckpoints : normalCheckpoints).push_back(checkpoint);
	}
	AddObjectGroup(GLFW_KEY_4, "Normal checkpoint", normalCheckpoints, 1.0f, 4.2f);
	AddObjectGroup(GLFW_KEY_5, "Rare checkpoint", rareCheckpoints, 1.3f, 5.0f);

	// 6: exit marker
	std::vector<const CompositeObject*> exitMarker;
	if (level.GetExitMarker() != nullptr) exitMarker.push_back(level.GetExitMarker());
	AddObjectGroup(GLFW_KEY_6, "Exit marker", exitMarker, 1.0f, 5.0f);

	// 7: robot
	AddObjectGroup(GLFW_KEY_7, "Robot", { &robot }, 1.3f, 5.0f);

	// 8: the cave mouth, seen from outside
	glm::vec3 mouth = layout.TileCenter(layout.EntranceCol(), layout.EntranceRow() + 1) + glm::vec3(0.0f, 1.8f, 0.0f);
	groups.push_back({ GLFW_KEY_8, "Cave entrance", { { mouth + glm::normalize(glm::vec3(0.35f, 0.25f, 1.0f)) * 10.0f, mouth } }, 0 });

	// 9: standing at the east end of the main chamber, looking towards the pillars in the west
	glm::vec3 eye = layout.Place(7, 4, 1.0f, 1.0f) + glm::vec3(0.0f, 2.2f, 0.0f);
	glm::vec3 look = layout.Place(3, 3, 0.0f, 0.0f) + glm::vec3(0.0f, 1.4f, 0.0f);
	groups.push_back({ GLFW_KEY_9, "Main chamber", { { eye, look } }, 0 });
}

void DemoViews::AddObjectGroup(int key, const std::string& name, const std::vector<const CompositeObject*>& objects,
	float lookHeight, float distance, const glm::vec3& viewDirection) {
	Group group{ key, name, {}, 0 };

	for (const CompositeObject* object : objects) {
		float scale = (object->scale.x + object->scale.y + object->scale.z) / 3.0f;

		glm::vec3 center = object->position + glm::vec3(0.0f, lookHeight * scale, 0.0f);

		// Where the camera goes relative to the object (+Z is its front at rotation 0), then turned with the object
		glm::vec3 direction = glm::normalize(viewDirection);
		direction = glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(object->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(direction, 0.0f));

		group.views.push_back({ center + direction * distance * scale, center });
	}

	groups.push_back(group);
}

void DemoViews::Update() {
	for (Group& group : groups) {
		// KeyPressed has to be called every frame, so it comes first
		if (controller.KeyPressed(group.key) && !group.views.empty()) {
			const View& view = group.views[group.next];
			controller.FlyTo(view.position, view.target);

			std::cout << "View: " << group.name;
			if (group.views.size() > 1) {
				std::cout << " " << (group.next + 1) << "/" << group.views.size();
			}
			std::cout << std::endl;

			group.next = (group.next + 1) % group.views.size();
		}
	}
}

glm::vec3 DemoViews::OverviewPosition() {
	return glm::vec3(12.0f, 20.0f, 20.0f);
}

glm::vec3 DemoViews::OverviewTarget() {
	return glm::vec3(0.0f, 0.0f, 1.0f);
}

void DemoViews::PrintHelp() {
	std::cout <<
		"\nCamera controls\n"
		"  W A S D      move forward / left / back / right\n"
		"  E / Q        move up / down          (hold Shift to go 3x faster)\n"
		"  Right mouse  hold and drag to look around (arrow keys turn too)\n"
		"  Mouse wheel  change the movement speed\n"
		"Close-up views (press again for the next object of that kind)\n"
		"  0 overview   1 treasure chest   2 coins   3 gems   4 normal checkpoints\n"
		"  5 rare checkpoint   6 exit marker   7 robot   8 cave entrance   9 inside the main chamber\n"
		"Other\n"
		"  C            switch the wall cutaway on/off (off = full-height walls; the close-up views\n"
		"               are made for the cutaway being on, with it off the camera can end up inside a wall)\n"
		"  Esc          quit\n"
		<< std::endl;
}
