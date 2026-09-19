#ifndef CYLINDER_CLASS_H
#define CYLINDER_CLASS_H

#include "Primitive.h"

// Geometry only (no OpenGL calls): side wall + top cap + bottom cap.
MeshData BuildCylinderMesh(float radius, float height, int sectors, const glm::vec3& color);

// Cylinder centered on the origin, its axis along Y. `sectors` = number of sides.
class Cylinder : public Primitive {
public:
	Cylinder(float radius = 0.5f, float height = 1.0f, int sectors = 48, const glm::vec3& color = glm::vec3(1.0f));
};

#endif
