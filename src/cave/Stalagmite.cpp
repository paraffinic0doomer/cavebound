#include "Stalagmite.h"

#include "primitives/Cone.h"

Stalagmite::Stalagmite(const glm::vec3& color)
	: CompositeObject("Stalagmite") {

	// Small clusters keep the walkable floor readable and match the shortened ceiling drips.
	AddPart(std::make_unique<Cone>(0.5f, 1.0f, 7, color),
		glm::vec3(0.0f, 0.48f, 0.0f), glm::vec3(0.0f), glm::vec3(0.62f, 0.96f, 0.62f));
	AddPart(std::make_unique<Cone>(0.5f, 1.0f, 7, color * 0.9f),
		glm::vec3(0.30f, 0.25f, 0.13f), glm::vec3(0.0f), glm::vec3(0.34f, 0.50f, 0.34f));
	AddPart(std::make_unique<Cone>(0.5f, 1.0f, 7, color * 1.1f),
		glm::vec3(-0.27f, 0.20f, -0.18f), glm::vec3(0.0f), glm::vec3(0.30f, 0.40f, 0.30f));
}
