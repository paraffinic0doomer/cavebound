#include "Sphere.h"

#include <cmath>
#include <glm/gtc/constants.hpp>

MeshData BuildSphereMesh(float radius, int sectors, int stacks, const glm::vec3& color) {
	MeshData data;
	const float pi = glm::pi<float>();

	// Vertices: (stacks + 1) rings of (sectors + 1) vertices. The first and last vertex of a ring
	// share a position (the seam) but are stored twice.
	for (int i = 0; i <= stacks; i++) {
		float phi = pi * i / stacks; // 0 = top pole, pi = bottom pole
		float y = radius * std::cos(phi);
		float ringRadius = radius * std::sin(phi);

		for (int j = 0; j <= sectors; j++) {
			float theta = 2.0f * pi * j / sectors;
			glm::vec3 position(ringRadius * std::cos(theta), y, ringRadius * std::sin(theta));

			// Per-vertex color variation (brighter on top, two bright/dark bands around) - not lighting
			float shade = 0.65f + 0.15f * std::cos(phi) + 0.20f * std::cos(2.0f * theta);
			data.vertices.push_back({ position, color * shade });
		}
	}

	// Indices: every ring segment is a quad made of two triangles. The triangle that would
	// collapse to a line at a pole is skipped.
	for (int i = 0; i < stacks; i++) {
		for (int j = 0; j < sectors; j++) {
			GLuint a = i * (sectors + 1) + j; // this ring
			GLuint b = a + sectors + 1;       // ring below

			if (i != 0)
				data.indices.insert(data.indices.end(), { a, a + 1, b });
			if (i != stacks - 1)
				data.indices.insert(data.indices.end(), { a + 1, b + 1, b });
		}
	}

	return data;
}

Sphere::Sphere(float radius, int sectors, int stacks, const glm::vec3& color)
	: Primitive(BuildSphereMesh(radius, sectors, stacks, color)) {
}
