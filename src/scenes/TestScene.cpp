#include "TestScene.h"

#include "primitives/Cube.h"
#include "primitives/Sphere.h"
#include "primitives/Cylinder.h"
#include "primitives/Cone.h"

using namespace std;
using namespace glm;

void BuildTestScene(vector<unique_ptr<Primitive>>& scene) {
	auto add = [&scene](unique_ptr<Primitive> primitive, vec3 position, vec3 rotation, vec3 scale) {
		primitive->position = position;
		primitive->rotation = rotation;
		primitive->scale = scale;
		scene.push_back(std::move(primitive));
	};

	// Ground slab: a cube scaled flat and wide
	add(make_unique<Cube>(1.0f, vec3(0.40f, 0.34f, 0.30f)), vec3(0.0f, -1.6f, -1.0f), vec3(0.0f), vec3(13.0f, 0.2f, 8.0f));

	// Front row: one of each primitive
	add(make_unique<Cube>(1.0f, vec3(0.90f, 0.45f, 0.30f)),           vec3(-4.5f, 0.0f, 0.0f), vec3(20.0f, 35.0f, 0.0f), vec3(1.6f));
	add(make_unique<Sphere>(0.5f, 48, 24, vec3(1.00f, 0.80f, 0.20f)), vec3(-1.5f, 0.0f, 0.0f), vec3(0.0f),               vec3(1.8f));
	add(make_unique<Cylinder>(0.5f, 1.0f, 48, vec3(0.40f, 0.60f, 0.90f)), vec3(1.5f, 0.0f, 0.0f), vec3(0.0f),            vec3(1.2f, 2.0f, 1.2f));
	add(make_unique<Cone>(0.5f, 1.0f, 48, vec3(0.30f, 0.80f, 0.40f)),     vec3(4.5f, 0.0f, 0.0f), vec3(0.0f),            vec3(1.4f, 2.2f, 1.4f));

	// Back row: rotations and non-uniform scale
	add(make_unique<Cube>(1.0f, vec3(0.65f, 0.40f, 0.85f)),           vec3(-4.5f, 2.6f, -3.0f), vec3(0.0f, 45.0f, 0.0f), vec3(1.4f));
	add(make_unique<Cylinder>(0.5f, 1.0f, 48, vec3(0.80f, 0.80f, 0.80f)), vec3(-4.5f, 2.6f, -3.0f), vec3(0.0f, 0.0f, 90.0f), vec3(0.4f, 3.4f, 0.4f)); // passes through the cube
	add(make_unique<Cone>(0.5f, 1.0f, 48, vec3(1.00f, 0.55f, 0.15f)),     vec3(0.0f, 2.6f, -3.0f),  vec3(0.0f, 0.0f, 180.0f), vec3(1.4f, 1.8f, 1.4f)); // upside down
	add(make_unique<Sphere>(0.5f, 48, 24, vec3(0.25f, 0.75f, 0.75f)), vec3(3.5f, 2.4f, -3.0f),  vec3(0.0f),               vec3(2.2f, 1.0f, 1.6f)); // ellipsoid

	// Near the camera: intersecting the ground and tilted, to verify depth testing
	add(make_unique<Sphere>(0.5f, 48, 24, vec3(0.85f, 0.25f, 0.30f)), vec3(-1.0f, -1.5f, 2.5f), vec3(0.0f),               vec3(1.6f)); // half buried in the ground
	add(make_unique<Cone>(0.5f, 1.0f, 48, vec3(0.95f, 0.85f, 0.30f)),     vec3(2.5f, -0.55f, 2.5f), vec3(0.0f, 0.0f, -35.0f), vec3(1.0f, 1.6f, 1.0f));
}
