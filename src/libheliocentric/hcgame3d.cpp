#include "heliocentric/hcgame3d.hpp"
#include <iostream>
#include <vector>
#include <string>

//#define super HcGame;

using namespace std;

HcGame3D::HcGame3D(int width, int height, string title, bool resizable, bool fullscreen, Camera& camera)
		: camera(camera), HcGame(width, height, title, resizable, fullscreen) {
}

void HcGame3D::resized(int width, int height) {
	HcGame::resized(width, height);
	camera.updateAspect(width, height);
}

void HcGame3D::init() {
	// Enable face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	// Enable depth testing with clamping
	glEnable(GL_DEPTH_TEST);
	glDepthMask(true);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);

	// Enable depth clamping if available (OpenGL 3.2)
	if (glversion(3, 2)) {
		glEnable(GL_DEPTH_CLAMP);
	}
}

void HcGame3D::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	renderWorld(getCamera().getWorldToCameraMatrix());
	glDisable(GL_DEPTH_TEST);
	renderHUD(mat4());
}

Camera& HcGame3D::getCamera() {
	return camera;
}

void HcGame3D::setCamera(Camera& camera) {
	this->camera = camera;
}