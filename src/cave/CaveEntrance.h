#ifndef CAVE_ENTRANCE_CLASS_H
#define CAVE_ENTRANCE_CLASS_H

#include "primitives/CompositeObject.h"
#include "CaveLayout.h"

// The cave mouth: two stone posts, a lintel across the top with a diamond keystone, two boulders
// and a grassy apron of ground in front of the cave. Everything is built from Cube and Sphere primitives.
class CaveEntrance : public CompositeObject {
public:
	CaveEntrance(const CaveLayout& layout);
};

#endif
