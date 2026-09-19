#include "GameObject.h"

GameObject::GameObject(std::string name) : CompositeObject(std::move(name)) {
}

void GameObject::Draw(Shader& shader) {
	// All parts of the game objects are opaque, so the opaque pass draws everything.
	DrawOpaque(shader);
}

void GameObject::SetPosition(const glm::vec3& newPosition) {
	position = newPosition;
}

void GameObject::SetRotation(const glm::vec3& newRotation) {
	rotation = newRotation;
}

void GameObject::SetScale(const glm::vec3& newScale) {
	scale = newScale;
}

void GameObject::SetScale(float uniformScale) {
	scale = glm::vec3(uniformScale);
}
