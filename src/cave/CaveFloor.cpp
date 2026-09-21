#include "CaveFloor.h"

#include "primitives/Cube.h"

CaveFloor::CaveFloor(const CaveLayout& layout, int sectionIndex)
	: CompositeObject("Floor") {
	const CaveSectionInfo& section = layout.Sections()[sectionIndex];

	// One broad floor per section removes the tiled-room look. The rock decorations break up the
	// silhouette while the uneven colour keeps the floor readable without drawing a grid.
	glm::vec3 position = layout.TileCenter(section.col0, section.row0)
		+ glm::vec3((section.col1 - section.col0) * CaveLayout::TILE * 0.5f,
			-CaveLayout::SLAB / 2.0f,
			(section.row1 - section.row0) * CaveLayout::TILE * 0.5f);
	glm::vec3 size((section.col1 - section.col0 + 1) * CaveLayout::TILE,
		CaveLayout::SLAB, (section.row1 - section.row0 + 1) * CaveLayout::TILE);
	AddPart(std::make_unique<Cube>(1.0f, section.floorColor), position, glm::vec3(0.0f), size);
}
