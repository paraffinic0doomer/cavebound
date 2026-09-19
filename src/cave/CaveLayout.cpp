#include "CaveLayout.h"

CaveLayout::CaveLayout() {
	// name, north-west tile, south-east tile, floor color.
	// The order matters only for who builds a shared wall block (see WallOwner).
	sections = {
		// Subtle warm variations keep the separate sections readable without making the cave look tiled.
		{ "Entrance",     5, 8, 5, 8, glm::vec3(0.37f, 0.31f, 0.24f) },
		{ "Main tunnel",  5, 5, 5, 7, glm::vec3(0.31f, 0.27f, 0.23f) },
		{ "Main chamber", 3, 3, 7, 4, glm::vec3(0.34f, 0.30f, 0.27f) },
		{ "Left tunnel",  1, 4, 2, 4, glm::vec3(0.30f, 0.29f, 0.27f) },
		{ "Right tunnel", 8, 4, 9, 4, glm::vec3(0.32f, 0.28f, 0.24f) },
		{ "Dead end 1",   4, 1, 4, 2, glm::vec3(0.29f, 0.25f, 0.22f) },
		{ "Dead end 2",   6, 0, 6, 2, glm::vec3(0.30f, 0.26f, 0.23f) },
		{ "Dead end 3",   3, 6, 4, 6, glm::vec3(0.31f, 0.27f, 0.24f) },
	};

	for (int row = 0; row < ROWS; row++)
		for (int col = 0; col < COLS; col++)
			sectionAt[row][col] = -1;

	for (int i = 0; i < static_cast<int>(sections.size()); i++) {
		const CaveSectionInfo& s = sections[i];
		for (int row = s.row0; row <= s.row1; row++)
			for (int col = s.col0; col <= s.col1; col++)
				sectionAt[row][col] = i;
	}

	// The entrance is the first section; the way in continues south from its (only) tile
	entranceCol = sections[0].col0;
	entranceRow = sections[0].row0;
}

int CaveLayout::SectionAt(int col, int row) const {
	if (col < 0 || col >= COLS || row < 0 || row >= ROWS) return -1; // outside the plan = rock
	return sectionAt[row][col];
}

bool CaveLayout::IsEntranceGap(int col, int row) const {
	return col == entranceCol && row == entranceRow + 1;
}

int CaveLayout::WallOwner(int col, int row) const {
	if (IsOpen(col, row) || IsEntranceGap(col, row)) return -1;

	for (int i = 0; i < static_cast<int>(sections.size()); i++) {
		for (int dr = -1; dr <= 1; dr++)
			for (int dc = -1; dc <= 1; dc++)
				if (SectionAt(col + dc, row + dr) == i) return i;
	}
	return -1; // solid rock nobody can see: no block needed
}

glm::vec3 CaveLayout::TileCenter(int col, int row) const {
	float x = (col - (COLS - 1) / 2.0f) * TILE;
	float z = (row - (ROWS - 1) / 2.0f) * TILE;
	return glm::vec3(x, 0.0f, z);
}

glm::vec3 CaveLayout::Place(int col, int row, float dx, float dz) const {
	return TileCenter(col, row) + glm::vec3(dx, 0.0f, dz);
}

float CaveLayout::Hash(int a, int b) {
	unsigned int h = static_cast<unsigned int>(a) * 73856093u ^ static_cast<unsigned int>(b) * 19349663u;
	h = (h ^ (h >> 13)) * 1274126177u;
	h ^= h >> 16;
	return (h & 0xFFFFu) / 65535.0f;
}
