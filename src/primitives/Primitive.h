#ifndef PRIMITIVE_CLASS_H
#define PRIMITIVE_CLASS_H

#include <glm/glm.hpp>

#include "core/Mesh.h"
#include "core/shaderClass.h"

// model = Translate * RotateY * RotateX * RotateZ * Scale   (rotation in degrees)
// Read from the right: the shape is scaled first, then rotated, then moved.
glm::mat4 BuildModelMatrix(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);

// Base class of every primitive shape (Cube, Sphere, Cylinder, Cone).
// A derived class only builds its geometry (MeshData); the transform and drawing are shared here.
// All primitives are built centered on the origin, so rotation happens around their own center.
class Primitive {
public:
	glm::vec3 position;
	glm::vec3 rotation; // Euler angles in degrees (x = pitch, y = yaw, z = roll)
	glm::vec3 scale;
	float alpha;        // 1.0 = opaque, < 1.0 = translucent

	Primitive(const MeshData& data);
	virtual ~Primitive() = default;

	glm::mat4 GetModelMatrix() const;

	// Sends the model matrix to the shader and draws the mesh.
	// The second version places the primitive inside a parent: model = parentMatrix * own matrix.
	void Draw(Shader& shader);
	void Draw(Shader& shader, const glm::mat4& parentMatrix);
	void Delete();

private:
	Mesh mesh;
};

#endif
