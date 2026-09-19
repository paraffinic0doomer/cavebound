#ifndef EXIT_MARKER_CLASS_H
#define EXIT_MARKER_CLASS_H

#include "GameObject.h"

// The exit marker, built from primitives:
//
//   ExitMarker
//    |- green pad       two Cylinder discs forming a bright ring on the floor
//    |- floor arrow     a Cube shaft and a flat 3-sided Cone as the arrow head, pointing along +Z
//    '- gate            two posts with green lamp spheres and a green sign board between them
//
// With rotation (0,0,0) the arrow points towards +Z (south), i.e. out of the cave, and the gate stands
// behind the pad on its -Z side. Size: about 2.4 wide, 2.2 tall.
class ExitMarker : public GameObject {
public:
	ExitMarker();
};

#endif
