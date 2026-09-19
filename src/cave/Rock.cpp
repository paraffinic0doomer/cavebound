#include "Rock.h"

#include "primitives/Sphere.h"
#include "primitives/Cone.h"

// Low-poly sphere: 7 sectors x 4 stacks instead of the smooth 48 x 24
static std::unique_ptr<Primitive> Lump(const glm::vec3& color) {
	return std::make_unique<Sphere>(0.5f, 7, 4, color);
}

Rock::Rock(RockSize size, const glm::vec3& color)
	: CompositeObject(size == RockSize::Large ? "Large rock" : "Small rock") {

	if (size == RockSize::Large) {
		// Overlapping faceted lumps look more like a fractured boulder than a tilted cube.
		AddPart(Lump(color),         glm::vec3( 0.00f, 0.32f,  0.00f), glm::vec3(0.0f,   0.0f, 0.0f), glm::vec3(1.75f, 1.22f, 1.55f));
		AddPart(Lump(color * 0.88f), glm::vec3( 0.72f, 0.18f,  0.32f), glm::vec3(0.0f,  35.0f, 0.0f), glm::vec3(1.15f, 0.82f, 1.08f));
		AddPart(Lump(color * 1.08f), glm::vec3(-0.65f, 0.15f,  0.46f), glm::vec3(0.0f, -20.0f, 0.0f), glm::vec3(0.95f, 0.72f, 0.92f));
		AddPart(std::make_unique<Cone>(0.5f, 1.0f, 6, color * 0.82f),
			glm::vec3(0.05f, 0.62f, -0.46f), glm::vec3(10.0f, 28.0f, -12.0f), glm::vec3(0.62f, 0.75f, 0.62f));
	}
	else {
		// One flat pebble with a small faceted chip.
		AddPart(Lump(color), glm::vec3(0.00f, 0.10f, 0.00f), glm::vec3(0.0f), glm::vec3(0.55f, 0.38f, 0.50f));
		AddPart(std::make_unique<Cone>(0.5f, 1.0f, 6, color * 0.82f),
			glm::vec3(0.25f, 0.16f, 0.08f), glm::vec3(5.0f, 30.0f, 0.0f), glm::vec3(0.18f, 0.28f, 0.18f));
	}
}
