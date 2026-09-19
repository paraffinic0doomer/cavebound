#include "CaveFloor.h"

#include "primitives/Cube.h"

CaveFloor::CaveFloor(const CaveLayout& layout, int sectionIndex)
	: CompositeObject("Floor") {
	const CaveSectionInfo& section = layout.Sections()[sectionIndex];

	for (int row = section.row0; row <= section.row1; row++) {
		for (int col = section.col0; col <= section.col1; col++) {
			// Keep adjacent floor tiles close in value; large colour jumps read as floor tiles, not stone.
			float brightness = 0.94f + 0.09f * CaveLayout::Hash(col, row);

			// A unit cube scaled into a flat slab, sunk so its top face is exactly at y = 0
			glm::vec3 position = layout.TileCenter(col, row) + glm::vec3(0.0f, -CaveLayout::SLAB / 2.0f, 0.0f);
			glm::vec3 size(CaveLayout::TILE, CaveLayout::SLAB, CaveLayout::TILE);

			AddPart(std::make_unique<Cube>(1.0f, section.floorColor * brightness), position, glm::vec3(0.0f), size);
		}
	}
}
