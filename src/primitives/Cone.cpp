#include "Cone.h"

#include <cmath>
#include <glm/gtc/constants.hpp>

MeshData BuildConeMesh(float radius, float height, int sectors, const glm::vec3& color) {
	MeshData data;
	const float pi = glm::pi<float>();
	const float top = height / 2.0f;
	const float bottom = -height / 2.0f;

	// --- Side: one apex vertex (index 0) and a ring of base vertices (index 1 .. sectors + 1) ---
	data.vertices.push_back({ glm::vec3(0.0f, top, 0.0f), color });
	for (int j = 0; j <= sectors; j++) {
		float theta = 2.0f * pi * j / sectors;
		float shade = 0.70f + 0.30f * std::cos(2.0f * theta); // per-vertex color variation, not lighting
		data.vertices.push_back({ glm::vec3(radius * std::cos(theta), bottom, radius * std::sin(theta)), color * shade });
	}
	for (int j = 0; j < sectors; j++) {
		GLuint a = 1 + j;
		GLuint b = a + 1;
		data.indices.insert(data.indices.end(), { 0, b, a });
	}

	// --- Base cap: triangle fan around a center vertex, facing down ---
	glm::vec3 capColor = color * 0.5f;
	GLuint center = static_cast<GLuint>(data.vertices.size());
	data.vertices.push_back({ glm::vec3(0.0f, bottom, 0.0f), capColor });
	for (int j = 0; j <= sectors; j++) {
		float theta = 2.0f * pi * j / sectors;
		data.vertices.push_back({ glm::vec3(radius * std::cos(theta), bottom, radius * std::sin(theta)), capColor });
	}
	for (int j = 0; j < sectors; j++) {
		GLuint a = center + 1 + j;
		data.indices.insert(data.indices.end(), { center, a, a + 1 });
	}

	return data;
}

Cone::Cone(float radius, float height, int sectors, const glm::vec3& color)
	: Primitive(BuildConeMesh(radius, height, sectors, color)) {
}
