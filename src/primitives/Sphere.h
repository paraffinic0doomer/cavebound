#ifndef SPHERE_CLASS_H
#define SPHERE_CLASS_H

#include "Primitive.h"

// Geometry only (no OpenGL calls): a latitude/longitude ("UV") sphere.
MeshData BuildSphereMesh(float radius, int sectors, int stacks, const glm::vec3& color);

// Sphere centered on the origin.
// sectors = slices around the Y axis (longitude), stacks = slices from pole to pole (latitude).
class Sphere : public Primitive {
public:
	Sphere(float radius = 0.5f, int sectors = 48, int stacks = 24, const glm::vec3& color = glm::vec3(1.0f));
};

#endif
