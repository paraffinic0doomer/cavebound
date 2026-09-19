#ifndef CAVE_FLOOR_CLASS_H
#define CAVE_FLOOR_CLASS_H

#include "primitives/CompositeObject.h"
#include "CaveLayout.h"

// Floor of one cave section: one flat stone slab (a scaled Cube) per tile.
// Each tile gets a slightly different brightness so the floor reads as paving stones.
class CaveFloor : public CompositeObject {
public:
	CaveFloor(const CaveLayout& layout, int sectionIndex);
};

#endif
