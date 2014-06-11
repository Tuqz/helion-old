#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

/**
 * It is very important to call updateAspect after instatiating a Camera object,
 * because otherwise, the frustum scale will not be set properly.
 */
class Camera {
private:
	mat4 cameraToClip, worldToCamera, worldToCameraRot;
	// Perspective data
	float frustumScale, zNear, zFar;
	// Orientation data
	vec3 position;
	float fPan, fTilt, fRoll;
	quat orientation;
	bool dirChanged, posChanged;
public:
	Camera(float zNear, float zFar, float frustumScale);
	// Matrix getters
	mat4 getWorldToClipMatrix();
	mat4 getCameraToClipMatrix();
	mat4 getWorldToCameraMatrix();
	// Perspective functions
	void setRanges(float zNear, float zFar);
	float getZNear();
	float getZFar();
	void setFrustumScale(float frustumScale);
	float getFrustumScale();
	void updateAspect(int width, int height);
	// Orientation functions
	void setPosition(vec3 position);
	vec3 getPosition();
	void move(vec3 translation);
	void moveRelative(vec3 translation);
	void move(float x, float y, float z);
	void moveRelative(float x, float y, float z);
	void pan(float angle);
	void tilt(float angle);
	void roll(float angle);
};

