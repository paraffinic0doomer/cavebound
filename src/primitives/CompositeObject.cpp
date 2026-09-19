#include "CompositeObject.h"

CompositeObject::CompositeObject(std::string name)
	: name(std::move(name)), position(0.0f), rotation(0.0f), scale(1.0f) {
}

Primitive& CompositeObject::AddPart(std::unique_ptr<Primitive> part,
	const glm::vec3& partPosition, const glm::vec3& partRotation, const glm::vec3& partScale) {
	part->position = partPosition;
	part->rotation = partRotation;
	part->scale = partScale;

	parts.push_back(std::move(part));
	return *parts.back();
}

CompositeObject& CompositeObject::AddChild(std::unique_ptr<CompositeObject> child) {
	children.push_back(std::move(child));
	return *children.back();
}

glm::mat4 CompositeObject::GetModelMatrix() const {
	return BuildModelMatrix(position, rotation, scale);
}

void CompositeObject::DrawOpaque(Shader& shader) {
	DrawPass(shader, glm::mat4(1.0f), false);
}

void CompositeObject::DrawTransparent(Shader& shader) {
	DrawPass(shader, glm::mat4(1.0f), true);
}

void CompositeObject::DrawPass(Shader& shader, const glm::mat4& parentMatrix, bool transparentPass) {
	glm::mat4 world = parentMatrix * GetModelMatrix();

	for (auto& part : parts) {
		bool isTransparent = part->alpha < 1.0f;
		if (isTransparent == transparentPass) {
			part->Draw(shader, world);
		}
	}
	for (auto& child : children) {
		child->DrawPass(shader, world, transparentPass);
	}
}

int CompositeObject::CountPrimitives() const {
	int count = static_cast<int>(parts.size());
	for (const auto& child : children) {
		count += child->CountPrimitives();
	}
	return count;
}

void CompositeObject::Delete() {
	for (auto& part : parts) {
		part->Delete();
	}
	for (auto& child : children) {
		child->Delete();
	}
	parts.clear();
	children.clear();
}
