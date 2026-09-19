#ifndef STALAGMITE_CLASS_H
#define STALAGMITE_CLASS_H

#include "primitives/CompositeObject.h"

// A stalagmite: a rock spike growing up from the floor. Three Cones with the tip pointing up.
// The object's origin is the point where it touches the floor.
class Stalagmite : public CompositeObject {
public:
	Stalagmite(const glm::vec3& color);
};

#endif
