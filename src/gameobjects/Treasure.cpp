#include "Treasure.h"

#include "primitives/Cube.h"
#include "primitives/Cylinder.h"
#include "primitives/Sphere.h"

namespace {
const glm::vec3 WOOD(0.46f, 0.26f, 0.11f);
const glm::vec3 LID_WOOD(0.54f, 0.31f, 0.14f);
const glm::vec3 IRON(0.24f, 0.24f, 0.27f);
const glm::vec3 GOLD(1.00f, 0.78f, 0.18f);
const glm::vec3 KEYHOLE(0.05f, 0.04f, 0.03f);

// Size of the box in world units (before the object's own scale)
const float LENGTH = 1.50f; // along X
const float HEIGHT = 0.70f;
const float DEPTH = 0.90f;  // along Z
}

Treasure::Treasure() : GameObject("Treasure chest") {
	// Wooden box: a unit cube stretched to LENGTH x HEIGHT x DEPTH, standing on the floor
	AddPart(std::make_unique<Cube>(1.0f, WOOD),
		glm::vec3(0.0f, HEIGHT / 2.0f, 0.0f), glm::vec3(0.0f), glm::vec3(LENGTH, HEIGHT, DEPTH));

	// Curved lid: a cylinder turned 90 degrees around Z so it lies along X. Its axis is on the top of
	// the box, so only the upper half sticks out and forms the rounded lid. Its diameter equals DEPTH.
	AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 10, LID_WOOD),
		glm::vec3(0.0f, HEIGHT, 0.0f), glm::vec3(0.0f, 0.0f, 90.0f), glm::vec3(DEPTH, LENGTH, DEPTH));

	// Two iron bands wrap the box (slightly larger than it) ...
	for (float side = -1.0f; side <= 1.0f; side += 2.0f) {
		AddPart(std::make_unique<Cube>(1.0f, IRON),
			glm::vec3(side * 0.48f, HEIGHT / 2.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.14f, HEIGHT + 0.02f, DEPTH + 0.05f));

		// ... and two iron rings (thin cylinders, a little wider than the lid) continue them over the lid
		AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 10, IRON),
			glm::vec3(side * 0.48f, HEIGHT, 0.0f), glm::vec3(0.0f, 0.0f, 90.0f), glm::vec3(DEPTH + 0.06f, 0.16f, DEPTH + 0.06f));
	}

	// Gold lock plate on the front (+Z) with a dark keyhole in front of it
	AddPart(std::make_unique<Cube>(1.0f, GOLD),
		glm::vec3(0.0f, HEIGHT - 0.06f, DEPTH / 2.0f + 0.03f), glm::vec3(0.0f), glm::vec3(0.26f, 0.30f, 0.07f));
	AddPart(std::make_unique<Cube>(1.0f, KEYHOLE),
		glm::vec3(0.0f, HEIGHT - 0.09f, DEPTH / 2.0f + 0.07f), glm::vec3(0.0f), glm::vec3(0.07f, 0.12f, 0.04f));

	// Four gold studs on the bottom corners (low-poly spheres)
	for (float sx = -1.0f; sx <= 1.0f; sx += 2.0f) {
		for (float sz = -1.0f; sz <= 1.0f; sz += 2.0f) {
			AddPart(std::make_unique<Sphere>(0.5f, 6, 4, GOLD),
				glm::vec3(sx * (LENGTH / 2.0f - 0.03f), 0.09f, sz * (DEPTH / 2.0f - 0.03f)), glm::vec3(0.0f), glm::vec3(0.16f));
		}
	}
}
