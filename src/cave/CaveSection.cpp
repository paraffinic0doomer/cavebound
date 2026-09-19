#include "CaveSection.h"

#include "CaveFloor.h"
#include "CaveCeiling.h"
#include "CaveWalls.h"

CaveSection::CaveSection(const CaveLayout& layout, int sectionIndex)
	: CompositeObject(layout.Sections()[sectionIndex].name) {
	AddChild(std::make_unique<CaveFloor>(layout, sectionIndex));
	AddChild(std::make_unique<CaveCeiling>(layout, sectionIndex));
	AddChild(std::make_unique<CaveWalls>(layout, sectionIndex));
}
