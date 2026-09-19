#ifndef CONE_CLASS_H
#define CONE_CLASS_H

#include "Primitive.h"

// Geometry only (no OpenGL calls): sloped side + base cap.
MeshData BuildConeMesh(float radius, float height, int sectors, const glm::vec3& color);

// Cone centered on the origin: apex at +height/2, circular base at -height/2, axis along Y.
class Cone : public Primitive {
public:
	Cone(float radius = 0.5f, float height = 1.0f, int sectors = 48, const glm::vec3& color = glm::vec3(1.0f));
};

#endif
