#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include <memory>
#include <vector>

#include "primitives/Primitive.h"

// The Phase 1 primitive test scene: one of every primitive plus transformed variants
// (rotation, non-uniform scale, intersecting shapes). Run the game with --test to see it.
void BuildTestScene(std::vector<std::unique_ptr<Primitive>>& scene);

#endif
