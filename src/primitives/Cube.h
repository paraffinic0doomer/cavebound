#ifndef CUBE_CLASS_H
#define CUBE_CLASS_H

#include "Primitive.h"

// Geometry only (no OpenGL calls): 24 vertices (4 per face) and 12 triangles.
MeshData BuildCubeMesh(float size, const glm::vec3& color);

// Cube centered on the origin. `size` is the edge length.
class Cube : public Primitive {
public:
	Cube(float size = 1.0f, const glm::vec3& color = glm::vec3(1.0f));
};

#endif
