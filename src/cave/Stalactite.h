#ifndef STALACTITE_CLASS_H
#define STALACTITE_CLASS_H

#include "primitives/CompositeObject.h"

// A stalactite: a rock spike hanging from the ceiling. Three Cones, each rotated 180 degrees
// around Z so the tip points down. The object's origin is the point where it touches the ceiling.
class Stalactite : public CompositeObject {
public:
	Stalactite(const glm::vec3& color);
};

#endif
