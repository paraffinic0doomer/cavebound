cmake_minimum_required(VERSION 3.15)
project(Cavebound LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The bundled Libraries/lib/glfw3.lib is an MSVC (Visual Studio) build of GLFW.
if(NOT MSVC)
	message(FATAL_ERROR "Use the MSVC toolchain (Visual Studio 2022): the bundled glfw3.lib is an MSVC library.")
endif()

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Libraries)

add_executable(Cavebound
	${SRC_DIR}/Main.cpp

	# core: OpenGL wrappers (shader, buffers, mesh) and the camera
	${SRC_DIR}/core/shaderClass.cpp
	${SRC_DIR}/core/VAO.cpp
	${SRC_DIR}/core/VBO.cpp
	${SRC_DIR}/core/EBO.cpp
	${SRC_DIR}/core/Mesh.cpp
	${SRC_DIR}/core/Camera.cpp
	${SRC_DIR}/core/CameraController.cpp

	# primitives: reusable 3D shapes
	${SRC_DIR}/primitives/Primitive.cpp
	${SRC_DIR}/primitives/CompositeObject.cpp
	${SRC_DIR}/primitives/Cube.cpp
	${SRC_DIR}/primitives/Sphere.cpp
	${SRC_DIR}/primitives/Cylinder.cpp
	${SRC_DIR}/primitives/Cone.cpp

	# phase 2: static cave environment
	${SRC_DIR}/cave/CaveLayout.cpp
	${SRC_DIR}/cave/CaveFloor.cpp
	${SRC_DIR}/cave/CaveCeiling.cpp
	${SRC_DIR}/cave/CaveWalls.cpp
	${SRC_DIR}/cave/CaveSection.cpp
	${SRC_DIR}/cave/CaveEntrance.cpp
	${SRC_DIR}/cave/Rock.cpp
	${SRC_DIR}/cave/Pillar.cpp
	${SRC_DIR}/cave/Stalactite.cpp
	${SRC_DIR}/cave/Stalagmite.cpp
	${SRC_DIR}/cave/Cave.cpp

	# phase 3: static hierarchical exploration robot
	${SRC_DIR}/robot/Robot.cpp

	# phase 4: game objects (treasure chest, coins, gems, checkpoints, exit marker) and their placement
	${SRC_DIR}/gameobjects/GameObject.cpp
	${SRC_DIR}/gameobjects/Treasure.cpp
	${SRC_DIR}/gameobjects/Coin.cpp
	${SRC_DIR}/gameobjects/Gem.cpp
	${SRC_DIR}/gameobjects/Checkpoint.cpp
	${SRC_DIR}/gameobjects/ExitMarker.cpp
	${SRC_DIR}/gameobjects/LevelObjects.cpp

	# demo camera: number-key close-up views of every object
	${SRC_DIR}/demo/DemoViews.cpp

	# third party
	${LIB_DIR}/src/glad.c
)

# Our headers are included as "core/Mesh.h", "primitives/Cube.h", ... relative to src/.
# GLAD, GLFW and GLM headers live in Libraries/include.
target_include_directories(Cavebound PRIVATE
	${SRC_DIR}
	${LIB_DIR}/include
)

target_link_libraries(Cavebound PRIVATE
	${LIB_DIR}/lib/glfw3.lib
	opengl32
)

# The prebuilt glfw3.lib ships without a .pdb; silence the harmless "PDB not found" linker warning.
target_link_options(Cavebound PRIVATE /ignore:4099)

# The shaders are loaded at runtime from "shaders/" in the working directory,
# so copy that folder next to the executable.
add_custom_command(TARGET Cavebound POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_CURRENT_SOURCE_DIR}/shaders
		$<TARGET_FILE_DIR:Cavebound>/shaders
)

# Visual Studio: start Cavebound by default and run it from the folder that holds "shaders/".
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Cavebound)
set_target_properties(Cavebound PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)")
