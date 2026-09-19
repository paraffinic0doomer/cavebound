#include "CaveCeiling.h"

#include "primitives/Cube.h"

// A faint roof is only used so the fixed overview can reveal the static layout.
// Its dark stone colour keeps it from reading as a blue glass ceiling.
static const float CEILING_ALPHA = 0.16f; // 1.0 = solid roof
static const glm::vec3 CEILING_COLOR(0.30f, 0.27f, 0.24f);

CaveCeiling::CaveCeiling(const CaveLayout& layout, int sectionIndex)
	: CompositeObject("Ceiling") {
	const CaveSectionInfo& section = layout.Sections()[sectionIndex];

	for (int row = section.row0; row <= section.row1; row++) {
		for (int col = section.col0; col <= section.col1; col++) {
			// The slab's underside is exactly at y = HEIGHT
			glm::vec3 position = layout.TileCenter(col, row) + glm::vec3(0.0f, CaveLayout::HEIGHT + CaveLayout::SLAB / 2.0f, 0.0f);
			glm::vec3 size(CaveLayout::TILE, CaveLayout::SLAB, CaveLayout::TILE);

			float brightness = 0.88f + 0.12f * CaveLayout::Hash(col + 11, row + 17);
			AddPart(std::make_unique<Cube>(1.0f, CEILING_COLOR * brightness), position, glm::vec3(0.0f), size).alpha = CEILING_ALPHA;
		}
	}
}
