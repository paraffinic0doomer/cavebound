#include "Pillar.h"

#include "primitives/Cylinder.h"
#include "primitives/Sphere.h"

Pillar::Pillar(float height, const glm::vec3& color)
	: CompositeObject("Pillar") {
	const float baseHeight = 0.42f;
	const float shaftHeight = height - 2.0f * baseHeight;

	// A natural stone column: faceted, slightly wider at both contact points, and irregular at the middle.
	AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 7, color * 0.82f),
		glm::vec3(0.0f, baseHeight / 2.0f, 0.0f), glm::vec3(0.0f, 12.0f, 0.0f), glm::vec3(1.55f, baseHeight, 1.55f));
	AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 7, color),
		glm::vec3(0.0f, baseHeight + shaftHeight / 2.0f, 0.0f), glm::vec3(0.0f, 18.0f, 0.0f), glm::vec3(1.08f, shaftHeight, 1.02f));
	AddPart(std::make_unique<Sphere>(0.5f, 7, 4, color * 0.92f),
		glm::vec3(0.08f, height * 0.48f, -0.05f), glm::vec3(0.0f, 25.0f, 0.0f), glm::vec3(1.26f, 1.10f, 1.20f));
	AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 7, color * 0.88f),
		glm::vec3(0.0f, height - baseHeight / 2.0f, 0.0f), glm::vec3(0.0f, -8.0f, 0.0f), glm::vec3(1.45f, baseHeight, 1.45f));
}
