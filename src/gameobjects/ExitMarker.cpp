#include "ExitMarker.h"

#include "primitives/Cone.h"
#include "primitives/Cube.h"
#include "primitives/Cylinder.h"
#include "primitives/Sphere.h"

namespace {
const glm::vec3 GREEN(0.18f, 0.88f, 0.36f);
const glm::vec3 DARK_GREEN(0.05f, 0.22f, 0.10f);
const glm::vec3 PALE_GREEN(0.80f, 1.00f, 0.85f);
const glm::vec3 POST(0.20f, 0.22f, 0.21f);
}

ExitMarker::ExitMarker() : GameObject("Exit marker") {
	// Pad: bright green disc (radius 1.2) with a dark green disc on top (radius 1.0) -> a green ring
	AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 24, GREEN),
		glm::vec3(0.0f, 0.03f, 0.0f), glm::vec3(0.0f), glm::vec3(2.40f, 0.06f, 2.40f));
	AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 24, DARK_GREEN),
		glm::vec3(0.0f, 0.04f, 0.0f), glm::vec3(0.0f), glm::vec3(2.00f, 0.08f, 2.00f));

	// Arrow lying on the pad, pointing along +Z.
	// Shaft: a flat, long cube.
	AddPart(std::make_unique<Cube>(1.0f, GREEN),
		glm::vec3(0.0f, 0.10f, -0.25f), glm::vec3(0.0f), glm::vec3(0.26f, 0.05f, 0.85f));
	// Head: a cone with only 3 sides is a triangular pyramid; squashed flat it looks like a triangle from
	// above. A cone's first corner points along +X, so it is turned -90 degrees around Y to point along +Z.
	AddPart(std::make_unique<Cone>(0.5f, 1.0f, 3, GREEN),
		glm::vec3(0.0f, 0.10f, 0.40f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(0.90f, 0.05f, 0.90f));

	// Gate behind the pad: two posts, each with a lamp on top ...
	for (float side = -1.0f; side <= 1.0f; side += 2.0f) {
		AddPart(std::make_unique<Cylinder>(0.5f, 1.0f, 8, POST),
			glm::vec3(side * 1.0f, 0.95f, -0.85f), glm::vec3(0.0f), glm::vec3(0.16f, 1.90f, 0.16f));
		AddPart(std::make_unique<Sphere>(0.5f, 8, 5, GREEN),
			glm::vec3(side * 1.0f, 2.03f, -0.85f), glm::vec3(0.0f), glm::vec3(0.34f));
	}

	// ... and a sign board between them: a green cube with a paler strip on it
	AddPart(std::make_unique<Cube>(1.0f, GREEN),
		glm::vec3(0.0f, 1.65f, -0.85f), glm::vec3(0.0f), glm::vec3(2.00f, 0.50f, 0.10f));
	AddPart(std::make_unique<Cube>(1.0f, PALE_GREEN),
		glm::vec3(0.0f, 1.65f, -0.79f), glm::vec3(0.0f), glm::vec3(1.60f, 0.16f, 0.05f));
}
