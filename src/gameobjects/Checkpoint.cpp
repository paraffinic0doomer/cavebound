#include "Checkpoint.h"

#include "primitives/Cone.h"
#include "primitives/Cube.h"
#include "primitives/Cylinder.h"
#include "primitives/Sphere.h"

namespace {
const glm::vec3 STONE(0.16f, 0.15f, 0.15f);
const glm::vec3 METAL(0.55f, 0.58f, 0.60f);

const glm::vec3 TEAL(0.12f, 0.85f, 0.88f);

const glm::vec3 GOLD(1.00f, 0.76f, 0.16f);
const glm::vec3 VIOLET(0.62f, 0.20f, 0.86f);
const glm::vec3 ORB(0.98f, 0.55f, 1.00f);
}

Checkpoint::Checkpoint(CheckpointType type)
	: GameObject(type == CheckpointType::Normal ? "Normal checkpoint" : "Rare checkpoint"), type(type) {
	if (type == CheckpointType::Normal) {
		BuildNormal();
	}
	else {
		BuildRare();
	}
}

void Checkpoint::BuildNormal() {
	// Ring on the floor: a bright disc (radius 1.0) with a darker, slightly higher disc on it (radius 0.82).
	// Only a ring of the bright disc stays visible around the edge.
	AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 20, TEAL),
		glm::vec3(0.0f, 0.03f, 0.0f), glm::vec3(0.0f), glm::vec3(2.00f, 0.06f, 2.00f));
	AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 20, STONE),
		glm::vec3(0.0f, 0.04f, 0.0f), glm::vec3(0.0f), glm::vec3(1.64f, 0.08f, 1.64f));

	// Pole with a small round foot
	AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 8, METAL),
		glm::vec3(0.0f, 0.15f, 0.0f), glm::vec3(0.0f), glm::vec3(0.50f, 0.22f, 0.50f));
	AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 8, METAL),
		glm::vec3(0.0f, 0.90f, 0.0f), glm::vec3(0.0f), glm::vec3(0.14f, 1.80f, 0.14f));

	// Flag: a thin cube hanging from the top of the pole, plus a ball on the very top
	AddPart(std::make_unique<Cube>(1.0f, TEAL),
		glm::vec3(0.42f, 1.50f, 0.0f), glm::vec3(0.0f), glm::vec3(0.72f, 0.42f, 0.05f));
	AddPart(std::make_unique<Sphere>(0.5f, 8, 5, TEAL),
		glm::vec3(0.0f, 1.85f, 0.0f), glm::vec3(0.0f), glm::vec3(0.26f));
}

void Checkpoint::BuildRare() {
	// Two rings: a wide gold one (radius 1.4) and a violet one (radius 1.15) inside it, then a dark floor disc
	AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 24, GOLD),
		glm::vec3(0.0f, 0.03f, 0.0f), glm::vec3(0.0f), glm::vec3(2.80f, 0.06f, 2.80f));
	AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 24, VIOLET),
		glm::vec3(0.0f, 0.04f, 0.0f), glm::vec3(0.0f), glm::vec3(2.40f, 0.08f, 2.40f));
	AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 24, STONE),
		glm::vec3(0.0f, 0.05f, 0.0f), glm::vec3(0.0f), glm::vec3(2.00f, 0.10f, 2.00f));

	// Golden pole on a wider foot
	AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 10, GOLD),
		glm::vec3(0.0f, 0.18f, 0.0f), glm::vec3(0.0f), glm::vec3(0.70f, 0.26f, 0.70f));
	AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 10, GOLD),
		glm::vec3(0.0f, 1.20f, 0.0f), glm::vec3(0.0f), glm::vec3(0.18f, 2.40f, 0.18f));

	// Large violet banner with a gold strip along its top edge
	AddPart(std::make_unique<Cube>(1.0f, VIOLET),
		glm::vec3(0.62f, 1.90f, 0.0f), glm::vec3(0.0f), glm::vec3(1.10f, 0.70f, 0.06f));
	AddPart(std::make_unique<Cube>(1.0f, GOLD),
		glm::vec3(0.62f, 2.28f, 0.0f), glm::vec3(0.0f), glm::vec3(1.14f, 0.09f, 0.09f));

	// Glowing orb on top, held by a crown of four gold spikes leaning outwards (rotation tips each cone)
	AddPart(std::make_unique<Sphere>(0.5f, 10, 6, ORB),
		glm::vec3(0.0f, 2.68f, 0.0f), glm::vec3(0.0f), glm::vec3(0.42f));
	const float tip = 22.0f;
	AddPart(std::make_unique<Cone>(0.5f, 1.0f, 6, GOLD), glm::vec3( 0.26f, 2.52f, 0.0f), glm::vec3(0.0f, 0.0f, -tip), glm::vec3(0.14f, 0.42f, 0.14f));
	AddPart(std::make_unique<Cone>(0.5f, 1.0f, 6, GOLD), glm::vec3(-0.26f, 2.52f, 0.0f), glm::vec3(0.0f, 0.0f,  tip), glm::vec3(0.14f, 0.42f, 0.14f));
	AddPart(std::make_unique<Cone>(0.5f, 1.0f, 6, GOLD), glm::vec3(0.0f, 2.52f,  0.26f), glm::vec3( tip, 0.0f, 0.0f), glm::vec3(0.14f, 0.42f, 0.14f));
	AddPart(std::make_unique<Cone>(0.5f, 1.0f, 6, GOLD), glm::vec3(0.0f, 2.52f, -0.26f), glm::vec3(-tip, 0.0f, 0.0f), glm::vec3(0.14f, 0.42f, 0.14f));
}
