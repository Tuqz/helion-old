#include "heliocentric/camera.hpp"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace std;

Camera::Camera(float zNear, float zFar, float frustumScale) : worldToCamera(), cameraToClip(0.0f), orientation(), position() {
	setRanges(zNear, zFar);
	setFrustumScale(frustumScale);
	cameraToClip[2][3] = -1;
	dirChanged = true;
	posChanged = true;
}

mat4 Camera::getWorldToClipMatrix() {
	return getCameraToClipMatrix() * getWorldToCameraMatrix();
}

mat4 Camera::getCameraToClipMatrix() {
	return cameraToClip;
}

mat4 Camera::getWorldToCameraMatrix() {
	if (posChanged || dirChanged) {
		if (dirChanged) {
			worldToCameraRot = glm::mat4_cast(orientation);
		}
		worldToCamera = translate(worldToCameraRot, -getPosition());
		posChanged = false;
		dirChanged = false;
	}
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
}

float Camera::getFrustumScale() {
	return frustumScale;
}

void Camera::updateAspect(int width, int height) {
	cameraToClip[0][0] = frustumScale * ((float) height / (float) width);
	cameraToClip[1][1] = frustumScale;
}

void Camera::setPosition(vec3 position) {
	this->position = position;
	posChanged = true;
}

void Camera::move(vec3 translation) {
	setPosition(getPosition() + translation);
}

void Camera::move(float x, float y, float z) {
	move(vec3(x, y, z));
}

void Camera::moveRelative(vec3 translation) {
	move(vec3(transpose(worldToCameraRot) * vec4(translation, 1)));
}

void Camera::moveRelative(float x, float y, float z) {
	moveRelative(vec3(x, y, z));
}

vec3 Camera::getPosition() {
	return position;
}

quat orient(float angle, float x, float y, float z) {
	float f = sinf(angle / 2.0f);
	return quat(cosf(angle / 2.0f), x*f, y*f, z * f);
}

void Camera::pan(float angle) {
	orientation = normalize(orient(angle, 0, 1, 0) * orientation);
	dirChanged = true;
}

void Camera::tilt(float angle) {
	orientation = normalize(orient(angle, -1, 0, 0) * orientation);
	dirChanged = true;
}

void Camera::roll(float angle) {
	orientation = normalize(orient(angle, 0, 0, -1) * orientation);
	dirChanged = true;
}