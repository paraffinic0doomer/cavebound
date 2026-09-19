#ifndef PILLAR_CLASS_H
#define PILLAR_CLASS_H

#include "primitives/CompositeObject.h"

// A stone pillar that reaches from the floor to the ceiling:
// a Cube base, an 8-sided Cylinder shaft, and a Cube capital turned 45 degrees.
// Its origin is at the bottom center, so placing it on the floor is just a translation.
class Pillar : public CompositeObject {
public:
	Pillar(float height, const glm::vec3& color);
};

#endif
