#include "Primitive.h"

#include <glm/gtc/matrix_transform.hpp>

glm::mat4 BuildModelMatrix(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) {
	glm::mat4 model = glm::mat4(1.0f);

	// Read from the bottom up: the shape is scaled first, then rotated, then moved.
	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, scale);

	return model;
}

Primitive::Primitive(const MeshData& data)
	: position(0.0f), rotation(0.0f), scale(1.0f), alpha(1.0f), mesh(data) {
}

glm::mat4 Primitive::GetModelMatrix() const {
	return BuildModelMatrix(position, rotation, scale);
}

void Primitive::Draw(Shader& shader) {
	Draw(shader, glm::mat4(1.0f));
}

void Primitive::Draw(Shader& shader, const glm::mat4& parentMatrix) {
	shader.SetMat4("model", parentMatrix * GetModelMatrix());
	shader.SetFloat("alpha", alpha);
	mesh.Draw();
}

void Primitive::Delete() {
	mesh.Delete();
}
