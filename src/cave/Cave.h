#ifndef CAVE_CLASS_H
#define CAVE_CLASS_H

#include "primitives/CompositeObject.h"
#include "CaveLayout.h"

// The complete static cave. It is the root of a small scene graph:
//
//   Cave
//    |- CaveSection x 8  (Entrance, Main tunnel, Main chamber, Left tunnel, Right tunnel, Dead end 1-3)
//    |     '- CaveFloor, CaveCeiling, CaveWalls
//    |- CaveEntrance
//    |- Rock x 28 (9 large, 19 small)
//    |- Pillar x 3
//    |- Stalactite x 16
//    '- Stalagmite x 12
//
// Each group is created by its own Build... function called from the constructor. To show a group on
// its own during a demo, comment out the other calls in Cave::Cave().
class Cave : public CompositeObject {
public:
	Cave();

	const CaveLayout& GetLayout() const { return layout; }

private:
	CaveLayout layout;

	void BuildSections();     // floor + ceiling + walls of the chamber, all tunnels and dead ends
	void BuildEntrance();
	void BuildLargeRocks();
	void BuildSmallRocks();
	void BuildPillars();
	void BuildStalactites();
	void BuildStalagmites();
};

#endif
