#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

class Camera {
private:
	mat4 worldToCamera, cameraToClip;
	float frustumScale, zNear, zFar;
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
	void updateAspect();
};

