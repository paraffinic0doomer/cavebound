#ifndef GEM_CLASS_H
#define GEM_CLASS_H

#include "GameObject.h"

enum class GemType { Ruby, Emerald, Sapphire, Amethyst };

// A cut gem floating above the floor, built from three primitives with 6 sides each:
//
//   crown     Cone, tip up
//   girdle    thin Cylinder, the widest part
//   pavilion  Cone turned upside down (rotation z = 180), tip down
//
// With so few sides every side of a cone is a large flat "facet", and the per-vertex shading of the
// cones makes neighbouring facets differ in brightness. Size: about 0.7 wide and 1.0 tall.
class Gem : public GameObject {
public:
	Gem(GemType type);

	GemType GetType() const { return type; }

private:
	GemType type;
};

#endif
