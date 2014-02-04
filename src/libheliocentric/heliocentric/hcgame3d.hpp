#include "hcgame.hpp"
#include "camera.hpp"
#include <string>

class HcGame3D : public HcGame{
private:
	Camera& camera;
public:
	HcGame3D(int width, int height, std::string title, bool resizable, Camera& camera);
	virtual void resized();
	Camera& getCamera();
	void setCamera(Camera& camera);
protected:
	virtual void init();
	virtual void render();
	virtual void renderWorld(mat4 base) = 0;
	virtual void renderHUD(mat4 base) = 0;
};
