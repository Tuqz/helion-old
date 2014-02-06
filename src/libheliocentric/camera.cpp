#include "heliocentric/camera.hpp"
#include <iostream>

using namespace std;

Camera::Camera(float zNear, float zFar, float frustumScale) : worldToCamera(), cameraToClip(0.0f) {
	setRanges(zNear, zFar);
	setFrustumScale(frustumScale);
	cameraToClip[2][3] = -1;
}

mat4 Camera::getWorldToClipMatrix() {
	return worldToCamera * cameraToClip;
}

mat4 Camera::getCameraToClipMatrix() {
	return cameraToClip;
}

mat4 Camera::getWorldToCameraMatrix() {
	return worldToCamera;
}

void Camera::setRanges(float zNear, float zFar) {
	this->zNear = zNear;
	this->zFar = zFar;
	cameraToClip[2][2] = (zFar + zNear) / (zNear - zFar);
	cameraToClip[3][2] = (2 * zFar * zNear) / (zNear - zFar);
}

float Camera::getZNear() {
	return zNear;
}

float Camera::getZFar() {
	return zFar;
}

void Camera::setFrustumScale(float frustumScale) {
	this->frustumScale = frustumScale;
	cameraToClip[0][0] = frustumScale/* / ((float) Display.getWidth() / Display.getHeight())*/; //TODO
	cameraToClip[1][1] = frustumScale;
}

float Camera::getFrustumScale() {
	return frustumScale;
}

void Camera::updateAspect() {
	setFrustumScale(frustumScale);
}