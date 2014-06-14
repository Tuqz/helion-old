#include "hcgame.hpp"
#include "camera.hpp"
#include "entity.hpp"
#include <string>

class HcGame3D : public HcGame {
private:
    Camera& camera;
    Entity* root;
public:
    HcGame3D(int width, int height, std::string title, bool resizable, bool fullscreen, Camera& camera);
    virtual void resized(int width, int height);
    Camera& getCamera();
    void setCamera(Camera& camera);
    Entity* getRoot();
    void setRoot(Entity* root);
protected:
    virtual void init();
    virtual void update(double update);
    virtual void render();
    virtual void renderWorld(mat4 base) = 0;
    virtual void renderHUD(mat4 base) = 0;
};
