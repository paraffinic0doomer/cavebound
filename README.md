# Cavebound: The Lost Treasure Hunt

A small 3D computer graphics game in C++ with OpenGL 3.3 (core), GLFW, GLAD and GLM.
No game engine.

## Folder layout

```
CMakeLists.txt            CMake build (MSVC)
Project1.vcxproj          Visual Studio / MSBuild project (same sources)
README.md
src/
  Main.cpp                window, OpenGL setup, static render loop (cave, robot, game objects)
  core/                   OpenGL wrappers and the camera
    shaderClass.*           compile/link shaders, set uniforms
    VAO.*  VBO.*  EBO.*     thin wrappers over the OpenGL buffer objects
    Mesh.*                  Vertex, MeshData, and Mesh (owns VAO + VBO + EBO)
    Camera.*                view + perspective projection matrices, free-fly orientation
    CameraController.*      keyboard/mouse flying and smooth glides to a chosen view
  primitives/             reusable shapes, each in its own file
    Primitive.*             base class: position / rotation / scale, model matrix, Draw()
    Cube.*  Sphere.*  Cylinder.*  Cone.*
    CompositeObject.*    hierarchical group of primitives
  cave/                   Phase 2 static cave environment
    Cave.*                root object that assembles the complete scene
    CaveLayout.*          small, named cave plan (entrance, tunnels, chamber, dead ends)
    CaveFloor.* CaveCeiling.* CaveWalls.* CaveSection.* CaveEntrance.*
    Rock.* Pillar.* Stalactite.* Stalagmite.*
  robot/                  Phase 3 static hierarchical exploration robot
    Robot.*                body, head/eyes/antenna, arms, wheels, and physical flashlight
  gameobjects/            Phase 4 static game objects (each built from primitives)
    GameObject.*           base class: position / rotation / scale / Draw()
    Treasure.*  Coin.*  Gem.*  Checkpoint.*  ExitMarker.*
    LevelObjects.*         places 2 normal + 1 rare checkpoint, the chest, 12 coins, 6 gems, the exit
  demo/                   camera demo
    DemoViews.*            number keys 0-9 glide to a close-up of each kind of object
shaders/                  GLSL: default.vert, default.frag
Libraries/                third party code (do not edit)
  include/                  GLAD, GLFW, GLM, KHR headers
  lib/glfw3.lib             GLFW (MSVC build)
  src/glad.c                GLAD loader source
reference/                notes/experiments that are NOT part of the build
```

Includes inside `src/` are written relative to `src/`, e.g. `#include "core/Mesh.h"`.

## Build and run

CMake (from the project folder, in a Visual Studio 2022 Developer PowerShell):

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Debug
.\build\Debug\Cavebound.exe
```

Visual Studio / VS Code: build `Project1.vcxproj` (task "Build OpenGL project"),
then run `x64\Debug\Project1.exe` from the project folder.

The program loads `shaders/default.vert` and `shaders/default.frag` relative to the
working directory. The CMake build copies `shaders/` next to the executable.

## Camera controls (for demonstrations)

The game starts on a three-quarter overview of the whole cave.

| Key / mouse | Action |
|---|---|
| W A S D | move forward / left / back / right |
| E / Q | move up / down (hold Shift for 3x speed) |
| hold right mouse button + drag | look around (the arrow keys also turn) |
| mouse wheel | change the movement speed |
| 0 | overview of the whole cave |
| 1 / 2 / 3 | treasure chest / coins / gems |
| 4 / 5 | normal checkpoints / rare checkpoint |
| 6 / 7 | exit marker / robot |
| 8 / 9 | cave entrance (from outside) / inside the main chamber |
| C | wall cutaway on/off (off = full-height walls) |
| Esc | quit |

Pressing 1-9 glides the camera to a close-up. Pressing the same key again goes to the next object of that
kind (there are 12 coins, 6 gems and 2 normal checkpoints). Moving or looking cancels a glide.
The close-up views are made for the cutaway being on (the default); with it off, the camera can end up
inside a wall. Nothing collides yet, so the camera can fly through walls.

## Adding a new source file

Add it under the matching `src/` folder and list it in **both** `CMakeLists.txt`
and `Project1.vcxproj` (+ `Project1.vcxproj.filters`).
