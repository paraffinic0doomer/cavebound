#ifndef ROCK_CLASS_H
#define ROCK_CLASS_H

#include "primitives/CompositeObject.h"

enum class RockSize { Small, Large };

// A low-poly rock: a cluster of squashed 7-sided spheres plus one angular Cube chunk.
// Every part is scaled and rotated differently, then the whole cluster is placed as one object.
class Rock : public CompositeObject {
public:
	Rock(RockSize size, const glm::vec3& color);
};

#endif
