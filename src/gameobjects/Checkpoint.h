#ifndef CHECKPOINT_CLASS_H
#define CHECKPOINT_CLASS_H

#include "GameObject.h"

enum class CheckpointType { Normal, Rare };

// A checkpoint: a colored ring on the floor marking the spot, a pole standing in its middle, and a flag.
//
//   Normal  compact teal checkpoint: one ring, a 1.8 tall pole, a teal flag and a ball on top.
//   Rare    bigger and golden: two rings, a 2.4 tall pole, a large violet banner with a gold trim,
//           and a glowing orb on top held by a crown of four gold spikes.
//
// The flag points along +X and is flat in the XY plane, so it is seen from the south with rotation (0,0,0).
class Checkpoint : public GameObject {
public:
	Checkpoint(CheckpointType type);

	CheckpointType GetType() const { return type; }

private:
	CheckpointType type;

	void BuildNormal();
	void BuildRare();
};

#endif
