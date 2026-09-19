#ifndef CAVE_WALLS_CLASS_H
#define CAVE_WALLS_CLASS_H

#include "primitives/CompositeObject.h"
#include "CaveLayout.h"

// Walls of one cave section: a solid rock block (a scaled Cube) on every rock tile that touches the
// section. Block heights differ a little, so the top of the rock mass looks uneven instead of flat.
// The walls on the camera side are cut down low (the "cutaway", see CaveWalls.cpp) so the
// overview camera can look into the cave from an angle.
class CaveWalls : public CompositeObject {
public:
	CaveWalls(const CaveLayout& layout, int sectionIndex);

	// Switches the cutaway on or off. It is read when walls are built, so rebuild the Cave afterwards.
	static void SetCutaway(bool enabled);
	static bool IsCutaway();
};

#endif
