#ifndef TREASURE_CLASS_H
#define TREASURE_CLASS_H

#include "GameObject.h"

// The treasure chest, built from 12 primitives:
//
//   Treasure
//    |- wooden box        Cube stretched into a box
//    |- curved lid        Cylinder lying on its side (its lower half is hidden inside the box)
//    |- 2 iron bands      Cubes around the box
//    |- 2 iron rings      thin Cylinders around the lid
//    '- gold lock plate + keyhole, and 4 gold corner studs
//
// The lock is on the +Z side, so with rotation (0,0,0) the chest faces south, towards the entrance.
class Treasure : public GameObject {
public:
	Treasure();
};

#endif
