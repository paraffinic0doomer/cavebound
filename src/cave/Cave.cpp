#include "Cave.h"

#include <iostream>

#include "CaveSection.h"
#include "CaveEntrance.h"
#include "Rock.h"
#include "Pillar.h"
#include "Stalactite.h"
#include "Stalagmite.h"

// Where a decoration stands: a tile of the layout, an offset (dx, dz) from that tile's center,
// and a size multiplier for the whole object.
struct Placement {
	int col, row;
	float dx, dz;
	float size;
};

// ---- Placement tables (the tile numbers refer to the plan drawn in CaveLayout.h) ----

static const Placement LARGE_ROCKS[] = {
	{ 3, 4, -0.9f,  0.8f, 1.0f },  // chamber, south-west corner
	{ 7, 4,  0.9f,  0.8f, 1.0f },  // chamber, south-east corner
	{ 1, 4, -0.6f, -0.7f, 1.1f },  // left tunnel, at its end
	{ 2, 4,  0.0f, -1.0f, 0.8f },  // left tunnel, against the north wall
	{ 9, 4,  0.6f,  0.6f, 1.1f },  // right tunnel, at its end
	{ 4, 1,  0.2f, -0.6f, 0.9f },  // dead end 1, at its end
	{ 6, 0, -0.2f, -0.5f, 1.0f },  // dead end 2, at its end
	{ 3, 6, -0.6f,  0.0f, 0.9f },  // dead end 3, at its end
	{ 5, 6,  1.0f,  0.5f, 0.7f },  // main tunnel, by the wall
};

static const Placement SMALL_ROCKS[] = {
	{ 4, 4,  0.6f,  0.3f, 1.0f }, { 5, 4, -0.9f, -0.4f, 0.8f }, { 6, 4,  0.5f,  0.7f, 1.1f },
	{ 3, 3,  0.8f, -0.7f, 0.9f }, { 7, 3, -0.7f,  0.9f, 1.0f }, { 4, 3, -0.8f,  0.6f, 0.7f },
	{ 1, 4,  0.7f,  0.6f, 1.0f }, { 2, 4, -0.4f,  0.6f, 0.9f }, { 8, 4, -0.3f, -0.6f, 1.0f },
	{ 9, 4, -0.6f,  0.5f, 0.8f }, { 5, 5, -0.8f,  0.3f, 0.9f }, { 5, 7,  0.7f, -0.4f, 1.0f },
	{ 5, 6, -0.6f, -0.8f, 0.8f }, { 4, 6,  0.3f,  0.6f, 0.9f }, { 3, 6,  0.2f, -0.6f, 1.1f },
	{ 6, 1,  0.6f,  0.5f, 0.8f }, { 6, 2, -0.5f,  0.2f, 1.0f }, { 4, 2, -0.5f, -0.3f, 0.9f },
	{ 5, 8, -0.8f,  0.7f, 0.8f },
};

// Pillars stand in the main chamber, on the row nearest the dead ends
static const Placement PILLARS[] = {
	{ 3, 3, 0.0f, 0.0f, 1.0f },
	{ 5, 3, 0.0f, 0.0f, 1.0f },
	{ 7, 3, 0.0f, 0.0f, 1.0f },
};

static const Placement STALACTITES[] = {
	// Sparse clusters accent the cave shape; the earlier dense distribution made the roof look like a fence.
	{ 3, 4,  0.8f, -0.6f, 0.90f }, { 5, 4,  0.8f, -0.8f, 0.78f },
	{ 6, 3, -0.9f, -0.6f, 0.84f }, { 7, 4, -0.5f, -0.7f, 0.92f },
	{ 5, 3,  1.0f,  0.9f, 0.68f }, { 1, 4,  0.5f, -0.4f, 0.82f },
	{ 2, 4,  0.6f, -0.6f, 0.74f }, { 8, 4, -0.4f,  0.6f, 0.76f },
	{ 9, 4,  0.5f, -0.5f, 0.88f }, { 5, 5,  0.6f,  0.3f, 0.74f },
	{ 5, 7, -0.5f, -0.4f, 0.82f }, { 4, 1, -0.4f,  0.3f, 0.78f },
	{ 6, 0, -0.3f,  0.5f, 0.88f }, { 3, 6,  0.3f, -0.3f, 0.72f },
	{ 3, 3, -0.8f,  0.8f, 0.80f }, { 7, 3,  0.8f, -0.8f, 0.86f },
};

static const Placement STALAGMITES[] = {
	{ 3, 4,  0.9f, -0.9f, 0.82f }, { 5, 4,  0.9f,  0.9f, 0.88f },
	{ 6, 3,  0.8f,  0.8f, 0.80f }, { 7, 4, -0.9f, -0.9f, 0.76f },
	{ 1, 4, -0.5f,  0.8f, 0.82f }, { 2, 4,  0.5f, -0.9f, 0.86f },
	{ 8, 4,  0.6f,  0.8f, 0.78f }, { 9, 4, -0.7f, -0.8f, 0.82f },
	{ 5, 5,  0.9f, -0.6f, 0.76f }, { 5, 7, -0.8f,  0.5f, 0.84f },
	{ 6, 1,  0.5f,  0.4f, 0.80f }, { 3, 6, -0.6f,  0.6f, 0.72f },
};

template <size_t N>
static constexpr int Count(const Placement(&)[N]) { return static_cast<int>(N); }

// ---- Cave ----

Cave::Cave() : CompositeObject("Cave") {
	// Each line creates one group of objects. Comment a line out to leave that group out.
	BuildSections();
	BuildEntrance();
	BuildLargeRocks();
	BuildSmallRocks();
	BuildPillars();
	BuildStalactites();
	BuildStalagmites();

	std::cout << "Cave built: " << CountPrimitives() << " primitives" << std::endl;
}

void Cave::BuildSections() {
	// One CaveSection per named part of the layout (chamber, tunnels, dead ends).
	// Comment out a section to remove that tunnel (its floor, ceiling and walls).
	for (int i = 0; i < static_cast<int>(layout.Sections().size()); i++) {
		AddChild(std::make_unique<CaveSection>(layout, i));
	}
}

void Cave::BuildEntrance() {
	AddChild(std::make_unique<CaveEntrance>(layout));
}

void Cave::BuildLargeRocks() {
	for (int i = 0; i < Count(LARGE_ROCKS); i++) {
		const Placement& p = LARGE_ROCKS[i];
		float shade = 0.90f + 0.20f * CaveLayout::Hash(p.col, p.row * 13 + i);

		auto rock = std::make_unique<Rock>(RockSize::Large, glm::vec3(0.52f, 0.50f, 0.48f) * shade);
		rock->position = layout.Place(p.col, p.row, p.dx, p.dz);
		rock->rotation = glm::vec3(0.0f, 360.0f * CaveLayout::Hash(i, 17), 0.0f);
		rock->scale = glm::vec3(p.size);
		AddChild(std::move(rock));
	}
}

void Cave::BuildSmallRocks() {
	for (int i = 0; i < Count(SMALL_ROCKS); i++) {
		const Placement& p = SMALL_ROCKS[i];
		float shade = 0.90f + 0.20f * CaveLayout::Hash(p.col * 5 + 1, p.row + i);

		auto rock = std::make_unique<Rock>(RockSize::Small, glm::vec3(0.58f, 0.54f, 0.50f) * shade);
		rock->position = layout.Place(p.col, p.row, p.dx, p.dz);
		rock->rotation = glm::vec3(0.0f, 360.0f * CaveLayout::Hash(i, 29), 0.0f);
		rock->scale = glm::vec3(p.size);
		AddChild(std::move(rock));
	}
}

void Cave::BuildPillars() {
	for (int i = 0; i < Count(PILLARS); i++) {
		const Placement& p = PILLARS[i];

		auto pillar = std::make_unique<Pillar>(CaveLayout::HEIGHT, glm::vec3(0.72f, 0.68f, 0.62f));
		pillar->position = layout.Place(p.col, p.row, p.dx, p.dz);
		AddChild(std::move(pillar));
	}
}

void Cave::BuildStalactites() {
	for (int i = 0; i < Count(STALACTITES); i++) {
		const Placement& p = STALACTITES[i];

		// Hangs from the ceiling: its origin is the touching point, at y = HEIGHT
		auto stalactite = std::make_unique<Stalactite>(glm::vec3(0.78f, 0.72f, 0.62f));
		stalactite->position = layout.Place(p.col, p.row, p.dx, p.dz) + glm::vec3(0.0f, CaveLayout::HEIGHT, 0.0f);
		stalactite->rotation = glm::vec3(0.0f, 360.0f * CaveLayout::Hash(i, 41), 0.0f);
		stalactite->scale = glm::vec3(p.size);
		AddChild(std::move(stalactite));
	}
}

void Cave::BuildStalagmites() {
	for (int i = 0; i < Count(STALAGMITES); i++) {
		const Placement& p = STALAGMITES[i];

		auto stalagmite = std::make_unique<Stalagmite>(glm::vec3(0.70f, 0.60f, 0.46f));
		stalagmite->position = layout.Place(p.col, p.row, p.dx, p.dz);
		stalagmite->rotation = glm::vec3(0.0f, 360.0f * CaveLayout::Hash(i, 53), 0.0f);
		stalagmite->scale = glm::vec3(p.size);
		AddChild(std::move(stalagmite));
	}
}
