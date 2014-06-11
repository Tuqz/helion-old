#include "heliocentric/hcgame.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#define MIN_GL_VERSION_MAJOR 3 // For modern OpenGL
#define MIN_GL_VERSION_MINOR 1 // For UBO's

using namespace std;

// Static functions

void glfwErrorCallback(int error, const char* description) {
	cerr << "Error: " /*<< error << " - "*/ << description << endl;
}

int initHeliocentric() {
	glfwSetErrorCallback(glfwErrorCallback);
	return glfwInit();
}

void exitHeliocentric() {
	glfwTerminate();
}

bool glversion(int requiredMajor, int requiredMinor) {
	int actualMajor, actualMinor;
	glGetIntegerv(GL_MAJOR_VERSION, &actualMajor);
	glGetIntegerv(GL_MINOR_VERSION, &actualMinor);
	if (requiredMajor < actualMajor) {
		return true;
	}
	if (requiredMajor > actualMajor) {
		return false;
	}
	return requiredMinor <= actualMinor;
}

void getCurrentResolution(int* width, int* height) {
	const GLFWvidmode* return_struct = glfwGetVideoMode(glfwGetPrimaryMonitor());
	*height = return_struct->height;
	*width = return_struct->width;
}

// Callback functions

void cb_resized(GLFWwindow* window, int width, int height) {
	HcGame* wrapper = static_cast<HcGame*> (glfwGetWindowUserPointer(window));
	cout << "resizing: " << (wrapper == NULL ? "NULL" : "not NULL") << endl;
	wrapper->resized(width, height);
}

void cb_closed(GLFWwindow* window) {
	HcGame* wrapper = static_cast<HcGame*> (glfwGetWindowUserPointer(window));
	cout << "cb_closed" << endl;
	wrapper->closed();
}

void cb_scroll(GLFWwindow* window, double dx, double dy) {
	HcGame* wrapper = static_cast<HcGame*> (glfwGetWindowUserPointer(window));
	cout << "cb_scrolled" << endl;
	wrapper->scroll_dx += dx;
	wrapper->scroll_dy += dy;
}

// HCGame implementation

HcGame::HcGame(int width, int height, string title, bool resizable, bool fullscreen)
		: title(title), fps(0) {
	int screenWidth, screenHeight;
	getCurrentResolution(&screenWidth, &screenHeight);

	// Create the window and context
	glfwWindowHint(GLFW_VISIBLE, false);
	glfwWindowHint(GLFW_RESIZABLE, resizable);
	glfwWindowHint(GLFW_DECORATED, !fullscreen);
	GLFWmonitor* fullscreenMonitor = NULL;
	if (fullscreen) {
		width = screenWidth;
		height = screenHeight;
		//		fullscreenMonitor = glfwGetPrimaryMonitor();
	}
	window = glfwCreateWindow(width, height, title.c_str(), fullscreenMonitor, NULL);
	if (!window) {
		cerr << "Failed to create window." << endl;
		shutdown();
	}
	glfwMakeContextCurrent(window);

	// Center the window
	glfwSetWindowPos(window, (screenWidth - width) / 2, (screenHeight - height) / 2);

	// Check OpenGL version
	int major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	if (glversion(MIN_GL_VERSION_MAJOR, MIN_GL_VERSION_MINOR)) {
		cout << "OpenGL version: " << major << "." << minor << endl;
	} else {
		cerr << "Error: OpenGL version "
				<< MIN_GL_VERSION_MAJOR << "." << MIN_GL_VERSION_MINOR
				<< " required, but got " << major << "." << minor << endl;
		shutdown();
	}

	// Initialize glew for the current context
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		shutdown();
	}

	// Set up callbacks
	glfwSetWindowUserPointer(window, this);
	//	glfwSetFramebufferSizeCallback(window, cb_resized);
	glfwSetWindowCloseCallback(window, cb_closed);
	glfwSetScrollCallback(window, cb_scroll);

	// Show the window
	glfwShowWindow(window);
	glfwSwapBuffers(window); // Required to get the focus
}

void HcGame::run() {
	// Initalize prevTime and prevCalcTime
	getDelta();
	prevCalcTime = getTime();

	// Initialization
	init();

	float sleepTime;
	while (!shouldStop()) {
		// Handle window resizing
		resized();

		// Update the game state
		glfwPollEvents();
		update(getDelta());
		getMousePosition(&prev_x, &prev_y);
		scroll_dx = 0;
		scroll_dy = 0;

		// Draw the new frame
		render();

		// Switch draw buffers
		glfwSwapBuffers(window);

		// Update the FPS calculation
		updateFPS();

		// Cap fps to 60fps
		//TODO vsync
		sleepTime = 1.0f / 60 - (getTime() - prevTime);
		usleep((int) (sleepTime * 1000000));
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
	//TODO only called when pressing the x button - maybe this is desired behaviour?
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

void HcGame::getWindowSize(int* width, int* height) {
	glfwGetWindowSize(window, width, height);
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

// Input handling

bool HcGame::keyPressed(int key) {
	return glfwGetKey(window, key) == GLFW_PRESS;
}

void HcGame::getMousePosition(double* x, double* y) {
	glfwGetCursorPos(window, x, y);
}

void HcGame::setMousePosition(double x, double y) {
	glfwSetCursorPos(window, x, y);
	prev_x = x;
	prev_y = y;
}

void HcGame::getMouseMotion(double* dx, double* dy) {
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	*dx = x - prev_x;
	*dy = y - prev_y;
}

float HcGame::getScrollDX() {
	return scroll_dx;
}

float HcGame::getScrollDY() {
	return scroll_dy;
}

void HcGame::grabMouse() {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void HcGame::releaseMouse() {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void HcGame::setMouseGrabbed(bool grab) {
	if (grab) {
		grabMouse();
	} else {
		releaseMouse();
	}
}

bool HcGame::isMouseGrabbed() {
	return glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
}