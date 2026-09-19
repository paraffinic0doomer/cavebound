#include <algorithm>
#include <iostream>
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "core/shaderClass.h"
#include "core/Camera.h"
#include "core/CameraController.h"
#include "cave/Cave.h"
#include "cave/CaveWalls.h"
#include "robot/Robot.h"
#include "gameobjects/LevelObjects.h"
#include "demo/DemoViews.h"

using namespace std;
using namespace glm;

const unsigned int width = 1024;
const unsigned int height = 576;

// Keeps the viewport and the camera's aspect ratio in sync with the window size
void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight) {
	if (newWidth == 0 || newHeight == 0) return; // window minimized

	glViewport(0, 0, newWidth, newHeight);

	Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
	if (camera != nullptr) {
		camera->aspectRatio = static_cast<float>(newWidth) / static_cast<float>(newHeight);
	}
}

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Cavebound: The Lost Treasure Hunt", NULL, NULL);
	if (window == NULL) {
		cout << "Failed to create window!" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGL()) {
		cout << "Failed to initialize GLAD!" << endl;
		glfwTerminate();
		return -1;
	}
	cout << "OpenGL " << glGetString(GL_VERSION) << " | " << glGetString(GL_RENDERER) << endl;

	int framebufferWidth, framebufferHeight;
	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	glViewport(0, 0, framebufferWidth, framebufferHeight);

	// Shaders
	unique_ptr<Shader> shaderProgram;
	try {
		shaderProgram = make_unique<Shader>("shaders/default.vert", "shaders/default.frag");
	}
	catch (const exception& error) {
		cout << error.what() << endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	// The camera starts on a three-quarter overview from the south-east, about 42 degrees above the floor. It
	// looks into the cave over the low near-side walls (the cutaway in CaveWalls.cpp), so the whole plan and
	// everything in it is visible. It can then be flown around and sent to close-ups (see the controls below).
	// Moving the robot or any other object remains a later-phase feature.
	Camera camera(DemoViews::OverviewPosition(), DemoViews::OverviewTarget(),
		static_cast<float>(framebufferWidth) / static_cast<float>(framebufferHeight));
	glfwSetWindowUserPointer(window, &camera);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Static scene: the Phase 2 cave plus the Phase 3 robot. Neither object has movement yet.
	unique_ptr<Cave> cave = make_unique<Cave>();
	unique_ptr<Robot> robot = make_unique<Robot>();
	robot->SetPosition(vec3(0.0f, 0.0f, 0.0f)); // centre of the main chamber
	robot->SetRotation(vec3(0.0f, 0.0f, 0.0f));
	robot->SetScale(vec3(0.90f));
	robot->SetHeadRotation(vec3(0.0f, -12.0f, 0.0f)); // static pose: head branch turns with eyes and antenna

	// Phase 4: checkpoints, treasure chest, coins, gems and the exit marker, placed on the cave tiles.
	// They are only placed here; nothing can be collected or triggered yet.
	unique_ptr<LevelObjects> level = make_unique<LevelObjects>(cave->GetLayout());

	// Demo camera: keyboard/mouse flying plus number keys that glide to a close-up of each kind of object
	CameraController cameraController(window, camera);
	DemoViews demoViews(cameraController, cave->GetLayout(), *level, *robot);
	DemoViews::PrintHelp();

	// Depth testing: the closest fragment wins, whatever the drawing order
	glEnable(GL_DEPTH_TEST);
	// The ceiling is deliberately translucent so the overview camera can show the cave interior.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	double lastTime = glfwGetTime();

	while (glfwWindowShouldClose(window) == false) {
		double now = glfwGetTime();
		float deltaTime = static_cast<float>(std::min(now - lastTime, 0.1)); // capped so a stall cannot cause a jump
		lastTime = now;

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}

		// C: rebuild the cave with or without the cutaway walls
		if (cameraController.KeyPressed(GLFW_KEY_C)) {
			CaveWalls::SetCutaway(!CaveWalls::IsCutaway());
			cave->Delete();
			cave = make_unique<Cave>();
			cout << "Wall cutaway: " << (CaveWalls::IsCutaway() ? "on" : "off") << endl;
		}

		cameraController.Update(deltaTime);
		demoViews.Update();

		glClearColor(0.025f, 0.018f, 0.015f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram->Activate();
		shaderProgram->SetMat4("view", camera.GetViewMatrix());
		shaderProgram->SetMat4("proj", camera.GetProjectionMatrix());

		cave->DrawOpaque(*shaderProgram);
		robot->Draw(*shaderProgram);
		level->Draw(*shaderProgram);
		glDepthMask(GL_FALSE);
		cave->DrawTransparent(*shaderProgram);
		glDepthMask(GL_TRUE);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	cave->Delete();
	cave.reset();
	robot->Delete();
	robot.reset();
	level->Delete();
	level.reset();
	shaderProgram->Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
