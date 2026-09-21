#include "CaveCeiling.h"

#include "primitives/Cube.h"
#include "primitives/Sphere.h"

// A faint roof is only used so the fixed overview can reveal the static layout.
// Its dark stone colour keeps it from reading as a blue glass ceiling.
static const float CEILING_ALPHA = 0.10f;
static const glm::vec3 CEILING_COLOR(0.24f, 0.21f, 0.19f);

CaveCeiling::CaveCeiling(const CaveLayout& layout, int sectionIndex)
	: CompositeObject("Ceiling") {
	const CaveSectionInfo& section = layout.Sections()[sectionIndex];

	for (int row = section.row0; row <= section.row1; row++) {
		for (int col = section.col0; col <= section.col1; col++) {
			float variation = CaveLayout::Hash(col + 11, row + 17);
			glm::vec3 position = layout.TileCenter(col, row)
				+ glm::vec3((variation - 0.5f) * 0.7f, CaveLayout::HEIGHT + 0.25f * variation, (0.5f - variation) * 0.5f);
			glm::vec3 scale(CaveLayout::TILE * 1.25f, 0.65f + variation * 0.8f, CaveLayout::TILE * 1.20f);
			AddPart(std::make_unique<Sphere>(0.5f, 8, 5, CEILING_COLOR * (0.85f + variation * 0.2f)),
				position, glm::vec3(0.0f, variation * 25.0f, 0.0f), scale).alpha = CEILING_ALPHA;
		}
	}
}
