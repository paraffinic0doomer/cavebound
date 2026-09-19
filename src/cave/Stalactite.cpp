#include "Stalactite.h"

#include "primitives/Cone.h"

Stalactite::Stalactite(const glm::vec3& color)
	: CompositeObject("Stalactite") {
	const glm::vec3 flipped(0.0f, 0.0f, 180.0f); // turn the cone upside down

	// These are deliberately short. The earlier 1.6-unit main cone occupied nearly half the cave height.
	// Each flipped cone has its base at y = 0, so this object still touches the ceiling exactly.
	AddPart(std::make_unique<Cone>(0.5f, 1.0f, 7, color),
		glm::vec3(0.0f, -0.43f, 0.0f), flipped, glm::vec3(0.52f, 0.86f, 0.52f));
	// Two small mineral drips beside the main spike
	AddPart(std::make_unique<Cone>(0.5f, 1.0f, 7, color * 0.9f),
		glm::vec3(0.27f, -0.24f, 0.10f), flipped, glm::vec3(0.30f, 0.48f, 0.30f));
	AddPart(std::make_unique<Cone>(0.5f, 1.0f, 7, color * 1.1f),
		glm::vec3(-0.24f, -0.20f, -0.12f), flipped, glm::vec3(0.26f, 0.40f, 0.26f));
}
