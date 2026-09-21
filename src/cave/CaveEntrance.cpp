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

	// Low-poly boulders form a rough natural arch instead of a constructed doorway.
	AddPart(std::make_unique<Sphere>(0.5f, 8, 5, stone), glm::vec3(-1.35f, 1.1f, frontZ), glm::vec3(0.0f, 15.0f, 0.0f), glm::vec3(1.35f, 2.3f, 1.0f));
	AddPart(std::make_unique<Sphere>(0.5f, 8, 5, stone * 0.92f), glm::vec3(1.35f, 1.2f, frontZ), glm::vec3(0.0f, -20.0f, 0.0f), glm::vec3(1.3f, 2.2f, 1.0f));
	AddPart(std::make_unique<Sphere>(0.5f, 8, 5, stone * 0.86f), glm::vec3(0.0f, H - 0.05f, frontZ), glm::vec3(0.0f, 35.0f, 0.0f), glm::vec3(2.2f, 1.0f, 1.0f));
	AddPart(std::make_unique<Sphere>(0.5f, 7, 4, stone * 1.08f), glm::vec3(-0.55f, H + 0.35f, frontZ), glm::vec3(0.0f, 45.0f, 0.0f), glm::vec3(0.9f, 0.8f, 0.9f));
	AddPart(std::make_unique<Sphere>(0.5f, 7, 4, stone * 0.96f), glm::vec3(0.7f, H + 0.4f, frontZ), glm::vec3(0.0f, -25.0f, 0.0f), glm::vec3(1.0f, 0.75f, 0.9f));

	// Two boulders outside, one on each side
	AddPart(std::make_unique<Sphere>(0.5f, 7, 4, glm::vec3(0.55f, 0.52f, 0.50f)), glm::vec3(-2.7f, 0.4f, 2.0f), glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(1.5f, 1.1f, 1.3f));
	AddPart(std::make_unique<Sphere>(0.5f, 7, 4, glm::vec3(0.50f, 0.47f, 0.45f)), glm::vec3( 2.7f, 0.3f, 2.4f), glm::vec3(0.0f, -30.0f, 0.0f), glm::vec3(1.2f, 0.9f, 1.1f));

	// A muted earth apron frames the entrance without introducing an unrelated bright green plane.
	AddPart(std::make_unique<Cube>(1.0f, glm::vec3(0.20f, 0.16f, 0.11f)),
		glm::vec3(0.0f, -CaveLayout::SLAB / 2.0f, CaveLayout::TILE / 2.0f), glm::vec3(0.0f), glm::vec3(13.0f, CaveLayout::SLAB, 6.0f));
}
