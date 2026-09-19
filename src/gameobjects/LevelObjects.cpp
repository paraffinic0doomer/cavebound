#include "LevelObjects.h"

#include <iostream>

// Where an object stands: a tile of the layout (see the plan in CaveLayout.h), an offset (dx, dz)
// from the tile's center, a rotation around the vertical axis in degrees, and a size multiplier.
// The offsets were chosen to keep clear of the rocks, pillars and stalagmites of the cave.
struct Spot {
	int col, row;
	float dx, dz;
	float yaw;
	float scale;
};

struct GemSpot {
	Spot spot;
	GemType type;
};

// ---- Placement tables ----

static const Spot NORMAL_CHECKPOINTS[] = {
	{ 5, 7, -0.40f, -0.90f, 0.0f, 0.75f },  // main tunnel, near the entrance
	{ 4, 4, -0.50f, -0.30f, 0.0f, 0.75f },  // main chamber, west side
};

// Main chamber, at the mouth of dead end 2: the last checkpoint before the treasure
static const Spot RARE_CHECKPOINT = { 6, 3, -0.45f, -0.20f, 0.0f, 0.85f };

// Dead end 2, facing south (towards the way in)
static const Spot TREASURE_CHEST = { 6, 1, -0.55f, -0.45f, 0.0f, 1.0f };

// Entrance tile: the arrow on the pad points out of the cave
static const Spot EXIT_MARKER = { 5, 8, 0.0f, -0.55f, 0.0f, 0.8f };

static const Spot COINS[] = {
	// main tunnel, on the way in
	{ 5, 5,  0.00f, -0.05f,  20.0f, 1.0f },
	{ 5, 6, -0.10f,  0.00f, 300.0f, 1.0f },
	{ 5, 7,  0.40f,  0.45f,  70.0f, 1.0f },
	// main chamber
	{ 6, 4,  0.00f, -0.10f, 200.0f, 1.0f },
	{ 4, 3,  0.00f,  0.00f, 120.0f, 1.0f },
	{ 7, 4, -0.25f, -0.20f, 330.0f, 1.0f },
	// left and right tunnel
	{ 2, 4,  0.40f,  0.25f,  50.0f, 1.0f },
	{ 8, 4, -0.15f,  0.30f, 250.0f, 1.0f },
	// dead ends 1 and 3
	{ 4, 2,  0.20f,  0.20f, 160.0f, 1.0f },
	{ 4, 6, -0.05f, -0.20f, 100.0f, 1.0f },
	// on the way to the chest (dead end 2)
	{ 6, 2,  0.35f, -0.10f, 280.0f, 1.0f },
	{ 6, 1, -0.20f,  1.00f,  10.0f, 1.0f },
};

// One gem at the end of every branch, and one in the chamber
static const GemSpot GEMS[] = {
	{ { 1, 4,  0.90f, -0.25f, 0.0f, 1.15f }, GemType::Sapphire },  // end of the left tunnel
	{ { 9, 4,  0.55f, -0.95f, 0.0f, 1.15f }, GemType::Emerald  },  // end of the right tunnel
	{ { 4, 1, -1.00f,  0.05f, 0.0f, 1.15f }, GemType::Ruby     },  // end of dead end 1
	{ { 3, 6,  0.45f,  0.85f, 0.0f, 1.15f }, GemType::Amethyst },  // end of dead end 3
	{ { 6, 0,  0.00f,  0.95f, 0.0f, 1.15f }, GemType::Ruby     },  // end of dead end 2, behind the chest
	{ { 3, 4,  0.15f, -0.20f, 0.0f, 1.15f }, GemType::Emerald  },  // main chamber
};

template <size_t N>
static constexpr int Count(const Spot(&)[N]) { return static_cast<int>(N); }
template <size_t N>
static constexpr int Count(const GemSpot(&)[N]) { return static_cast<int>(N); }

// ---- LevelObjects ----

LevelObjects::LevelObjects(const CaveLayout& layout) : CompositeObject("Level objects"), layout(layout) {
	// Each line creates one group of objects. Comment a line out to leave that group out.
	BuildCheckpoints();
	BuildTreasure();
	BuildCoins();
	BuildGems();
	BuildExit();

	std::cout << "Level objects built: 2 normal checkpoints, 1 rare checkpoint, 1 treasure chest, "
		<< Count(COINS) << " coins, " << Count(GEMS) << " gems, 1 exit marker ("
		<< CountPrimitives() << " primitives)" << std::endl;
}

void LevelObjects::Draw(Shader& shader) {
	DrawOpaque(shader);
}

void LevelObjects::PlaceOnTile(std::unique_ptr<GameObject> object, int col, int row, float dx, float dz, float yaw, float scale) {
	object->SetPosition(layout.Place(col, row, dx, dz));
	object->SetRotation(glm::vec3(0.0f, yaw, 0.0f));
	object->SetScale(scale);
	AddChild(std::move(object));
}

void LevelObjects::BuildCheckpoints() {
	for (int i = 0; i < Count(NORMAL_CHECKPOINTS); i++) {
		const Spot& s = NORMAL_CHECKPOINTS[i];
		auto checkpoint = std::make_unique<Checkpoint>(CheckpointType::Normal);
		checkpoints.push_back(checkpoint.get());
		PlaceOnTile(std::move(checkpoint), s.col, s.row, s.dx, s.dz, s.yaw, s.scale);
	}

	const Spot& rare = RARE_CHECKPOINT;
	auto rareCheckpoint = std::make_unique<Checkpoint>(CheckpointType::Rare);
	checkpoints.push_back(rareCheckpoint.get());
	PlaceOnTile(std::move(rareCheckpoint), rare.col, rare.row, rare.dx, rare.dz, rare.yaw, rare.scale);
}

void LevelObjects::BuildTreasure() {
	const Spot& s = TREASURE_CHEST;
	auto chest = std::make_unique<Treasure>();
	treasure = chest.get();
	PlaceOnTile(std::move(chest), s.col, s.row, s.dx, s.dz, s.yaw, s.scale);
}

void LevelObjects::BuildCoins() {
	for (int i = 0; i < Count(COINS); i++) {
		const Spot& s = COINS[i];
		auto coin = std::make_unique<Coin>();
		coins.push_back(coin.get());
		PlaceOnTile(std::move(coin), s.col, s.row, s.dx, s.dz, s.yaw, s.scale);
	}
}

void LevelObjects::BuildGems() {
	for (int i = 0; i < Count(GEMS); i++) {
		const Spot& s = GEMS[i].spot;
		auto gem = std::make_unique<Gem>(GEMS[i].type);
		gems.push_back(gem.get());
		PlaceOnTile(std::move(gem), s.col, s.row, s.dx, s.dz, s.yaw, s.scale);
	}
}

void LevelObjects::BuildExit() {
	const Spot& s = EXIT_MARKER;
	auto marker = std::make_unique<ExitMarker>();
	exitMarker = marker.get();
	PlaceOnTile(std::move(marker), s.col, s.row, s.dx, s.dz, s.yaw, s.scale);
}
