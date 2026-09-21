#ifndef CAVE_LAYOUT_CLASS_H
#define CAVE_LAYOUT_CLASS_H

#include <string>
#include <vector>
#include <glm/glm.hpp>

// One named part of the cave: a rectangle of tiles (inclusive corners) with its own floor color.
struct CaveSectionInfo {
	std::string name;
	int col0, row0; // north-west tile
	int col1, row1; // south-east tile
	glm::vec3 floorColor;
};

// The cave plan. The cave is laid out on a grid of square tiles (TILE units wide, same as a tunnel).
// Columns run west -> east (x), rows run north -> south (z, the entrance is at the south / bottom).
// The plan is centered on the world origin, the floor top is at y = 0.
//
//   col:   0  1  2  3  4  5  6  7  8  9  10       . = solid rock
//   row 0  .  .  .  .  .  .  D2 .  .  .  .        E = Entrance        M = Main tunnel
//   row 1  .  .  .  .  D1 .  D2 .  .  .  .        H = Main chamber
//   row 2  .  .  .  .  D1 .  D2 .  .  .  .        L = Left tunnel     R = Right tunnel
//   row 3  .  .  .  H  H  H  H  H  .  .  .        D1, D2, D3 = dead-end tunnels
//   row 4  .  L  L  H  H  H  H  H  R  R  .
//   row 5  .  .  .  .  .  M  .  .  .  .  .
//   row 6  .  .  .  D3 D3 M  .  .  .  .  .
//   row 7  .  .  .  .  .  M  .  .  .  .  .
//   row 8  .  .  .  .  .  E  .  .  .  .  .
class CaveLayout {
public:
	static constexpr float TILE = 3.5f;       // comfortable alley width for the third-person robot
	static constexpr float HEIGHT = 3.5f;     // floor -> ceiling
	static constexpr float SLAB = 0.3f;       // thickness of floor and ceiling slabs
	static constexpr int COLS = 15;
	static constexpr int ROWS = 17;

	CaveLayout();

	const std::vector<CaveSectionInfo>& Sections() const { return sections; }

	int SectionAt(int col, int row) const; // index into Sections(), or -1 for solid rock
	bool IsOpen(int col, int row) const { return SectionAt(col, row) >= 0; }

	// The rock tile that must stay empty in front of the entrance so the way in stays open
	bool IsEntranceGap(int col, int row) const;

	// For a rock tile touching open space (also diagonally): the first section that touches it.
	// That section builds the wall block, so no block is ever built twice. -1 = no wall here.
	int WallOwner(int col, int row) const;

	int EntranceCol() const { return entranceCol; }
	int EntranceRow() const { return entranceRow; }

	// World position of a tile center at floor level (y = 0)
	glm::vec3 TileCenter(int col, int row) const;

	// World position at floor level, offset (dx, dz) from the center of a tile
	glm::vec3 Place(int col, int row, float dx, float dz) const;

	// Deterministic pseudo-random number in [0, 1] from two integers (same cave on every run)
	static float Hash(int a, int b);

private:
	std::vector<CaveSectionInfo> sections;
	int sectionAt[ROWS][COLS];
	int entranceCol, entranceRow;
};

#endif
