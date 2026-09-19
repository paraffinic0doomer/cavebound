#ifndef CAVE_SECTION_CLASS_H
#define CAVE_SECTION_CLASS_H

#include "primitives/CompositeObject.h"
#include "CaveLayout.h"

// One named part of the cave (main chamber, main tunnel, left tunnel, right tunnel, a dead end, ...).
// It is made of three child objects: CaveFloor, CaveCeiling and CaveWalls.
// Which section it builds comes from the layout, so tunnels are created individually and can be
// shown or hidden one by one (see Cave::BuildSections).
class CaveSection : public CompositeObject {
public:
	CaveSection(const CaveLayout& layout, int sectionIndex);
};

#endif
