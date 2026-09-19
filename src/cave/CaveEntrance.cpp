#include "CaveEntrance.h"

#include "primitives/Cube.h"
#include "primitives/Sphere.h"

CaveEntrance::CaveEntrance(const CaveLayout& layout)
	: CompositeObject("Cave entrance") {
	const float H = CaveLayout::HEIGHT;
	const glm::vec3 stone(0.42f, 0.36f, 0.29f);

	// The object's origin is the center of the open tile just in front of the entrance tile
	position = layout.TileCenter(layout.EntranceCol(), layout.EntranceRow() + 1);
	const float frontZ = CaveLayout::TILE / 2.0f - 0.5f; // the arch stands at the front of that tile

	// Two posts (stretched cubes)
	AddPart(std::make_unique<Cube>(1.0f, stone), glm::vec3(-1.2f, (H + 0.3f) / 2.0f, frontZ), glm::vec3(0.0f), glm::vec3(0.7f, H + 0.3f, 0.9f));
	AddPart(std::make_unique<Cube>(1.0f, stone), glm::vec3( 1.2f, (H + 0.3f) / 2.0f, frontZ), glm::vec3(0.0f), glm::vec3(0.7f, H + 0.3f, 0.9f));

	// Lintel across the top, and a keystone (a cube turned 45 degrees around Z, i.e. a diamond) above it
	AddPart(std::make_unique<Cube>(1.0f, stone * 0.9f), glm::vec3(0.0f, H - 0.15f, frontZ), glm::vec3(0.0f), glm::vec3(3.8f, 0.9f, 1.0f));
	AddPart(std::make_unique<Cube>(1.0f, stone * 1.1f), glm::vec3(0.0f, H + 0.55f, frontZ), glm::vec3(0.0f, 0.0f, 45.0f), glm::vec3(0.7f, 0.7f, 0.8f));

	// Two boulders outside, one on each side
	AddPart(std::make_unique<Sphere>(0.5f, 7, 4, glm::vec3(0.55f, 0.52f, 0.50f)), glm::vec3(-2.7f, 0.4f, 2.0f), glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(1.5f, 1.1f, 1.3f));
	AddPart(std::make_unique<Sphere>(0.5f, 7, 4, glm::vec3(0.50f, 0.47f, 0.45f)), glm::vec3( 2.7f, 0.3f, 2.4f), glm::vec3(0.0f, -30.0f, 0.0f), glm::vec3(1.2f, 0.9f, 1.1f));

	// A muted earth apron frames the entrance without introducing an unrelated bright green plane.
	AddPart(std::make_unique<Cube>(1.0f, glm::vec3(0.20f, 0.16f, 0.11f)),
		glm::vec3(0.0f, -CaveLayout::SLAB / 2.0f, CaveLayout::TILE / 2.0f), glm::vec3(0.0f), glm::vec3(13.0f, CaveLayout::SLAB, 6.0f));
}
