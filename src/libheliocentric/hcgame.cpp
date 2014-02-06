#include "heliocentric/hcgame.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

using namespace std;

// Static functions

void glfwErrorCallback(int error, const char* description) {
	cerr << "GLFW encountered error: " << error << " - " << description << endl;
}

int initHeliocentric() {
	glfwSetErrorCallback(glfwErrorCallback);
	return glfwInit();
}

void exitHeliocentric() {
	glfwTerminate();
}

bool glversion(int major, int minor) {
	int actualMajor, actualMinor;
	glGetIntegerv(GL_MAJOR_VERSION, &actualMajor);
	glGetIntegerv(GL_MINOR_VERSION, &actualMinor);
	if (major < actualMajor) {
		return false;
	}
	if (major > actualMajor) {
		return true;
	}
	if (minor < actualMinor) {
		return false;
	}
	return true;
}

// Callback functions

void cb_resized(GLFWwindow* window, int width, int height) {
	HcGame* wrapper = static_cast<HcGame*> (glfwGetWindowUserPointer(window));
	wrapper->resized(width, height);
}

void cb_closed(GLFWwindow* window) {
	HcGame* wrapper = static_cast<HcGame*> (glfwGetWindowUserPointer(window));
	cout << "cb_closed" << endl;
	wrapper->closed();
}

// HCGame implementation

HcGame::HcGame(int width, int height, string title, bool resizable) : title(title), fps(0) {

	// Create the window and context
	glfwWindowHint(GLFW_RESIZABLE, resizable);
	GLFWmonitor* fullscreenMonitor = NULL;
	//	if (fullscreen) {
	//		fullscreenMonitor = glfwGetPrimaryMonitor();
	//	}
	window = glfwCreateWindow(width, height, title.c_str(), fullscreenMonitor, NULL);
	if (!window) {
		shutdown();
	}
	glfwMakeContextCurrent(window);

	// Print OpenGL version
	int major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	cout << "OpenGL version: " << major << "." << minor << endl;
	
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		shutdown();
	}

	// Set up callbacks
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, cb_resized);
	glfwSetWindowCloseCallback(window, cb_closed);
}

void HcGame::run() {
	// Initalize prevTime and prevCalcTime
	getDelta();
	prevCalcTime = getTime();

	// Make sure the viewport and other window size related things are set right
	resized();

	// Initialization
	init();
	
	float sleepTime;
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
		//TODO vsync
		sleepTime = 1.0f / 60 - (getTime() - prevTime);
		usleep((int)(sleepTime*1000000)); 
		glfwPollEvents();
	}

	shutdown();
}

void HcGame::shutdown() { //TODO improve!!!
	glfwDestroyWindow(window);
	exitHeliocentric();
	exit(0);
}

bool HcGame::shouldStop() {
	return glfwWindowShouldClose(window) || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
}

// Display management

void HcGame::closed() {
	//TODO only called when pressing the x button
	// Intentionally left empty, so it can serve as a hook.
}

void HcGame::resized() {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	resized(width, height);
}

void HcGame::resized(int width, int height) {
	glViewport(0, 0, width, height);
}

void HcGame::setTitle(string title) {
	this->title = title;
}

string HcGame::getTitle() {
	return title;
}

// Time management

double HcGame::getTime() {
	return glfwGetTime();
}

double HcGame::getDelta() {
	double time = getTime();
	double delta = time - prevTime;
	prevTime = time;

	return delta;
}

void HcGame::updateFPS() {
	if (getTime() - prevCalcTime > 1) {
		glfwSetWindowTitle(window, (title + " - FPS: " + to_string(fps)).c_str());
		fps = 0;
		prevCalcTime += 1;
	}
	fps++;
}