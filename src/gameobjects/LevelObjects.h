#ifndef LEVEL_OBJECTS_CLASS_H
#define LEVEL_OBJECTS_CLASS_H

#include <memory>
#include <vector>

#include "primitives/CompositeObject.h"
#include "cave/CaveLayout.h"
#include "GameObject.h"
#include "Checkpoint.h"
#include "Coin.h"
#include "ExitMarker.h"
#include "Gem.h"
#include "Treasure.h"

// Places all Phase 4 game objects in the cave, using the tile plan from CaveLayout:
//
//   LevelObjects
//    |- Checkpoint x 2 normal + x 1 rare
//    |- Treasure     x 1
//    |- Coin         x 12
//    |- Gem          x 6
//    '- ExitMarker   x 1
//
// This is placement only: nothing here can be collected, triggered or animated.
// Like Cave, each group is created by its own Build... function called from the constructor;
// comment a call out in LevelObjects::LevelObjects() to leave that group out during a demo.
class LevelObjects : public CompositeObject {
public:
	explicit LevelObjects(const CaveLayout& layout);

	void Draw(Shader& shader);

	// Access to the placed objects by type. The pointers are owned by this object (they are children of it).
	Treasure* GetTreasure() const { return treasure; }
	const std::vector<Coin*>& GetCoins() const { return coins; }
	const std::vector<Gem*>& GetGems() const { return gems; }
	const std::vector<Checkpoint*>& GetCheckpoints() const { return checkpoints; } // normal and rare
	ExitMarker* GetExitMarker() const { return exitMarker; }

private:
	CaveLayout layout;

	Treasure* treasure = nullptr;
	std::vector<Coin*> coins;
	std::vector<Gem*> gems;
	std::vector<Checkpoint*> checkpoints;
	ExitMarker* exitMarker = nullptr;

	void BuildCheckpoints();
	void BuildTreasure();
	void BuildCoins();
	void BuildGems();
	void BuildExit();

	// Puts an object on a tile (offset dx, dz from the tile center), turned by `yaw` degrees around
	// the vertical axis and scaled by `scale`
	void PlaceOnTile(std::unique_ptr<GameObject> object, int col, int row, float dx, float dz, float yaw, float scale);
};

#endif
