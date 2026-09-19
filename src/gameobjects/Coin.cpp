#include "Coin.h"

#include "primitives/Cylinder.h"

namespace {
const glm::vec3 GOLD(1.00f, 0.78f, 0.15f);
const glm::vec3 LIGHT_GOLD(1.00f, 0.92f, 0.50f);
const glm::vec3 RIM_GOLD(0.85f, 0.60f, 0.08f);

const float HOVER = 0.45f;  // height of the coin's center above the floor
const float TILT = 30.0f;   // degrees around X: the face turns up and towards +Z
}

Coin::Coin() : GameObject("Coin") {
	const glm::vec3 center(0.0f, HOVER, 0.0f);
	const glm::vec3 tilt(TILT, 0.0f, 0.0f);

	// Darker, slightly bigger disc underneath: seen from the side it forms a rim around the coin
	AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 16, RIM_GOLD), center, tilt, glm::vec3(0.90f, 0.09f, 0.90f));

	// The coin itself: a 16-sided disc, 0.85 wide and 0.11 thick
	AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 16, GOLD), center, tilt, glm::vec3(0.85f, 0.11f, 0.85f));

	// Raised emblem in the middle: sticks out a little on both faces
	AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 12, LIGHT_GOLD), center, tilt, glm::vec3(0.50f, 0.14f, 0.50f));
}
