#include "Cube.h"

// Each face: outward normal, one tangent direction, and a brightness used to tint its vertex color.
// (This is just a per-vertex color variation so the faces can be told apart - it is not lighting.)
struct CubeFace {
	glm::vec3 normal;
	glm::vec3 tangent;
	float shade;
};

static const CubeFace faces[6] = {
	{ glm::vec3( 1, 0, 0), glm::vec3( 0, 0,-1), 0.80f }, // +X
	{ glm::vec3(-1, 0, 0), glm::vec3( 0, 0, 1), 0.60f }, // -X
	{ glm::vec3( 0, 1, 0), glm::vec3( 1, 0, 0), 1.00f }, // +Y (top)
	{ glm::vec3( 0,-1, 0), glm::vec3( 1, 0, 0), 0.45f }, // -Y (bottom)
	{ glm::vec3( 0, 0, 1), glm::vec3( 1, 0, 0), 0.90f }, // +Z (front)
	{ glm::vec3( 0, 0,-1), glm::vec3(-1, 0, 0), 0.55f }, // -Z (back)
};

MeshData BuildCubeMesh(float size, const glm::vec3& color) {
	MeshData data;
	const float h = size / 2.0f;

	// Corner offsets of a face in (tangent, bitangent) space, counter-clockwise seen from outside
	const float cornerU[4] = { -1.0f,  1.0f, 1.0f, -1.0f };
	const float cornerV[4] = { -1.0f, -1.0f, 1.0f,  1.0f };

	for (const CubeFace& face : faces) {
		// cross(normal, tangent) makes (tangent, bitangent, normal) a right-handed frame
		glm::vec3 bitangent = glm::cross(face.normal, face.tangent);
		GLuint first = static_cast<GLuint>(data.vertices.size());

		for (int i = 0; i < 4; i++) {
			glm::vec3 position = face.normal * h + face.tangent * (cornerU[i] * h) + bitangent * (cornerV[i] * h);
			data.vertices.push_back({ position, color * face.shade });
		}

		// Two triangles per face
		data.indices.insert(data.indices.end(), {
			first, first + 1, first + 2,
			first, first + 2, first + 3
		});
	}

	return data;
}

Cube::Cube(float size, const glm::vec3& color)
	: Primitive(BuildCubeMesh(size, color)) {
}
