#include "CaveWalls.h"

#include "primitives/Cube.h"
#include "primitives/Sphere.h"

static const glm::vec3 WALL_COLOR(0.27f, 0.235f, 0.21f);

// Cutaway ("dollhouse") view. The fixed camera looks at the cave from the south-east, and full-height walls
// (about 4 units) are taller than a tunnel is wide (3 units), so the walls on the near side would hide the
// floor behind them. With the cutaway on, those near-side walls are only CUTAWAY_HEIGHT tall while the far
// walls stay full height. The cutaway is on at startup; the C key in the game switches it off for a cave with
// full-height walls everywhere (e.g. when the camera is inside the cave).
static bool cutawayFrontWalls = false;
static const float CUTAWAY_HEIGHT = 1.1f;

void CaveWalls::SetCutaway(bool enabled) {
	cutawayFrontWalls = enabled;
}

bool CaveWalls::IsCutaway() {
	return cutawayFrontWalls;
}

// A wall block is on the camera side if open floor lies to its north or west (camera looks north-west)
static bool IsNearSideWall(const CaveLayout& layout, int col, int row) {
	return layout.IsOpen(col, row - 1) || layout.IsOpen(col - 1, row) || layout.IsOpen(col - 1, row - 1);
}

CaveWalls::CaveWalls(const CaveLayout& layout, int sectionIndex)
	: CompositeObject("Walls") {

	// Look one tile beyond the plan on every side: the outer walls are outside the grid
	for (int row = -1; row <= CaveLayout::ROWS; row++) {
		for (int col = -1; col <= CaveLayout::COLS; col++) {
			if (layout.WallOwner(col, row) != sectionIndex) continue;

			bool cutaway = cutawayFrontWalls && IsNearSideWall(layout, col, row);

			// A dark block seals the solid rock, then one low-poly boulder breaks up its square silhouette.
			float top = cutaway
				? CUTAWAY_HEIGHT + 0.25f * CaveLayout::Hash(col * 3 + 1, row * 5 + 2)
				: CaveLayout::HEIGHT + 0.25f + 0.65f * CaveLayout::Hash(col * 3 + 1, row * 5 + 2);
			float brightness = 0.82f + 0.20f * CaveLayout::Hash(col * 7 + 3, row * 11 + 5);

			// The block reaches from below the floor slab (y = -SLAB) up to `top`
			float sizeY = top + CaveLayout::SLAB;
			glm::vec3 position = layout.TileCenter(col, row) + glm::vec3(0.0f, (top - CaveLayout::SLAB) / 2.0f, 0.0f);
			glm::vec3 size(CaveLayout::TILE, sizeY, CaveLayout::TILE);

			AddPart(std::make_unique<Cube>(1.0f, WALL_COLOR * brightness), position, glm::vec3(0.0f), size);

			if (cutaway) continue; // low near-side walls stay plain blocks, so nothing blocks the view

			float xOffset = (CaveLayout::Hash(col, row + 31) - 0.5f) * 0.55f;
			float zOffset = (CaveLayout::Hash(col + 47, row) - 0.5f) * 0.55f;
			float boulderHeight = 1.15f + 0.45f * CaveLayout::Hash(col + 7, row + 19);
			glm::vec3 boulderPosition = layout.TileCenter(col, row) + glm::vec3(xOffset, boulderHeight * 0.5f, zOffset);
			glm::vec3 boulderScale(1.55f, boulderHeight * 2.0f, 1.45f);
			AddPart(std::make_unique<Sphere>(0.5f, 7, 4, WALL_COLOR * (brightness * 1.18f)),
				boulderPosition, glm::vec3(0.0f, 360.0f * CaveLayout::Hash(col + 3, row + 5), 0.0f), boulderScale);
		}
	}
}
