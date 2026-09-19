#include "Cylinder.h"

#include <cmath>
#include <glm/gtc/constants.hpp>

MeshData BuildCylinderMesh(float radius, float height, int sectors, const glm::vec3& color) {
	MeshData data;
	const float pi = glm::pi<float>();
	const float top = height / 2.0f;
	const float bottom = -height / 2.0f;

	// --- Side wall: for each angle a top vertex (index 2j) and a bottom vertex (index 2j + 1) ---
	for (int j = 0; j <= sectors; j++) {
		float theta = 2.0f * pi * j / sectors;
		float x = radius * std::cos(theta);
		float z = radius * std::sin(theta);
		float shade = 0.70f + 0.30f * std::cos(2.0f * theta); // per-vertex color variation, not lighting

		data.vertices.push_back({ glm::vec3(x, top, z), color * shade });
		data.vertices.push_back({ glm::vec3(x, bottom, z), color * shade });
	}
	for (int j = 0; j < sectors; j++) {
		GLuint topA = 2 * j, botA = 2 * j + 1;
		GLuint topB = 2 * j + 2, botB = 2 * j + 3;
		data.indices.insert(data.indices.end(), {
			topA, topB, botA,
			topB, botB, botA
		});
	}

	// --- Caps: a triangle fan around a center vertex. Own vertices so they get their own color. ---
	for (int cap = 0; cap < 2; cap++) {
		bool isTop = (cap == 0);
		float y = isTop ? top : bottom;
		glm::vec3 capColor = color * (isTop ? 1.0f : 0.5f);

		GLuint center = static_cast<GLuint>(data.vertices.size());
		data.vertices.push_back({ glm::vec3(0.0f, y, 0.0f), capColor });
		for (int j = 0; j <= sectors; j++) {
			float theta = 2.0f * pi * j / sectors;
			data.vertices.push_back({ glm::vec3(radius * std::cos(theta), y, radius * std::sin(theta)), capColor });
		}

		for (int j = 0; j < sectors; j++) {
			GLuint a = center + 1 + j;
			GLuint b = a + 1;
			// Winding is flipped between the caps so both face outwards
			if (isTop)
				data.indices.insert(data.indices.end(), { center, b, a });
			else
				data.indices.insert(data.indices.end(), { center, a, b });
		}
	}

	return data;
}

Cylinder::Cylinder(float radius, float height, int sectors, const glm::vec3& color)
	: Primitive(BuildCylinderMesh(radius, height, sectors, color)) {
}
