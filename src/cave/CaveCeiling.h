#ifndef CAVE_CEILING_CLASS_H
#define CAVE_CEILING_CLASS_H

#include "primitives/CompositeObject.h"
#include "CaveLayout.h"

// Ceiling of one cave section: one flat slab (a scaled Cube) per tile, HEIGHT above the floor.
//
// The slabs are translucent (alpha), otherwise the fixed overview camera could not look into the cave.
// Set CEILING_ALPHA to 1.0 in CaveCeiling.cpp to make the roof solid.
class CaveCeiling : public CompositeObject {
public:
	CaveCeiling(const CaveLayout& layout, int sectionIndex);
};

#endif
