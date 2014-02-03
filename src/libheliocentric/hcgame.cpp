#include "heliocentric/hcgame.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

using namespace std;

// Static functions

void glfwErrorCallback(int error, const char* description) {
	cerr << "GLFW encoutered error: " << error << " - " << description << endl;
}

int initHeliocentric() {
	glfwSetErrorCallback(glfwErrorCallback);
	return glfwInit();
}

void exitHeliocentric() {
	glfwTerminate();
}

// Callback functions

void cb_resized(GLFWwindow* window, int width, int height) {
	HCGame* wrapper = static_cast<HCGame*>(glfwGetWindowUserPointer(window));
	wrapper->resized(width, height);
}

void cb_closed(GLFWwindow* window) {
	HCGame* wrapper = static_cast<HCGame*>(glfwGetWindowUserPointer(window));
	cout << "cb_closed" << endl;
	wrapper->closed();
}

// HCGame implementation

HCGame::HCGame(int width, int height, string title, bool resizable) : title(title), fps(0) {
	
	// Create the window and context
	glfwWindowHint(GLFW_RESIZABLE, resizable);
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(window);
	
	// Set up callbacks
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, cb_resized);
	glfwSetWindowCloseCallback(window, cb_closed);
}

void HCGame::run() {
	// Initalize prevTime and prevCalcTime
	getDelta();
	prevCalcTime = getTime();

	// Make sure the viewport and other window size related things are set right
	resized();

	// Initialization
	init();

	while (!shouldStop()) {

		// Update the game state
		glfwPollEvents();
		update(getDelta());

		// Draw the new frame
		render();

		// Switch draw buffers
		glfwSwapBuffers(window);

		// Update the FPS calculation
		updateFPS();

		// Cap fps to 60fps
		usleep(16667); //TODO Fix to be calculated or to vsync
	}

	shutdown();
}

void HCGame::shutdown() {
	glfwDestroyWindow(window);
	exit(0);
}

bool HCGame::shouldStop() {
	return glfwWindowShouldClose(window) || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
}

// Display management

void HCGame::closed() {
	// Intentionally left empty, so I can serve as a hook.
}

void HCGame::resized() {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	resized(width, height);
}

void HCGame::resized(int width, int height) {
	glViewport(0, 0, width, height);
}

void HCGame::setDisplayMode() {
	//TODO
}

void HCGame::setTitle(string title) {
	this->title = title;
}

string HCGame::getTitle() {
	return title;
}

// Time management

double HCGame::getTime() {
	return glfwGetTime();
}

double HCGame::getDelta() {
	double time = getTime();
	double delta = time - prevTime;
	prevTime = time;

	return delta;
}

void HCGame::updateFPS() {
	if (getTime() - prevCalcTime > 1) {
		glfwSetWindowTitle(window, (title + " - FPS: " + to_string(fps)).c_str());
		fps = 0;
		prevCalcTime += 1;
	}
	fps++;
}