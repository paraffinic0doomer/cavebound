#ifndef COIN_CLASS_H
#define COIN_CLASS_H

#include "GameObject.h"

// A gold coin: a thin gold Cylinder disc with a smaller, lighter raised Cylinder on top (the emblem).
// It hovers a little above the floor and is tilted towards the viewer so its face and thickness both
// show. The tilt is part of the coin's shape, so rotation.y still turns the whole coin on the spot.
// Size: about 0.9 wide.
class Coin : public GameObject {
public:
	Coin();
};

#endif
