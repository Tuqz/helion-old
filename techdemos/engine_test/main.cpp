#include "heliocentric/hcgame3d.hpp"
#include "heliocentric/shaders.hpp"
#include "heliocentric/mesh.hpp"
#include "heliocentric/entity.hpp"
#include "heliocentric/matrixstack.hpp"
#include "heliocentric/objloader.hpp"
#include <glm/gtc/matrix_transform.hpp> 
#include <iostream>
#include <unistd.h>
#include <math.h>

#define super HcGame3D

using namespace std;

void printMatrix(mat4 matrix) {
    const float *values = (const float*) glm::value_ptr(matrix);
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            cout << values[r + 4 * c] << " ";
        }
        cout << endl;
    }
}

void printVector(vec3 vector) {
    cout << "pos = (" << vector.x << ", " << vector.y << ", " << vector.z << ")" << endl;
}

void setLightingUniforms(ShaderProgram& sp) {
    glUseProgram(sp.getProgram());
    GLint u;
    u = sp.getUniformLocation("sunIntensity");
    glUniform4f(u, 0.9f, 0.9f, 0.9f, 1);
    u = sp.getUniformLocation("ambientIntensity");
    glUniform4f(u, 0.1f, 0.1f, 0.1f, 1);
    u = sp.getUniformLocation("diffuseColor");
    glUniform4f(u, 1, 1, 1, 1);
    u = sp.getUniformLocation("attenuationFactor");
    glUniform1f(u, 1);
    glUseProgram(0);
}

void setSunPosition(ShaderProgram& sp, vec4 sunCameraPosition) {
    glUseProgram(sp.getProgram());
    glUniform3f(sp.getUniformLocation("sunPosition"), sunCameraPosition.x, sunCameraPosition.y, sunCameraPosition.z);
    glUseProgram(0);
}

void setCameraToClipMatrix(ShaderProgram& sp, Camera& cam) {
    glUseProgram(sp.getProgram());
    glUniformMatrix4fv(sp.getUniformLocation("cameraToClipMatrix"), 1, GL_FALSE, glm::value_ptr(cam.getCameraToClipMatrix()));
    glUseProgram(0);
}

class EngineTest : public HcGame3D {
private:
    ShaderProgram sp1, sp2;
    GLuint vao;

    Mesh mesh;
    Entity* sun;
    Entity* object1;
    Entity* object2;
    Entity* object3;

    GLuint testTexture, testTexSampler, testTexUnit = 0;
public:

    EngineTest(int width, int height, string title, bool resizable,
            bool fullscreen, Camera& camera)
    : HcGame3D(width, height, title, resizable, fullscreen, camera),
    sp1("data/shaders/simple.vert", "data/shaders/simple.frag"),
    sp2("data/shaders/texture.vert", "data/shaders/texture.frag") {
    }

    ~EngineTest() {
        delete sun;
        delete object1;
        delete object2;
        delete object3;
    }

    void init() {
        glClearColor(0.2f,0.2f,0.2f,1);
        glfwPollEvents();
        super::init();

        // Create vertex array
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // Set uniforms
        setLightingUniforms(sp1);
        setLightingUniforms(sp2);
        glUseProgram(sp2.getProgram());
        glUniform1i(sp2.getUniformLocation("testTexture"), testTexUnit);
        glUseProgram(0);

        // Load the mesh
        ObjLoader loader(sp2);
        loader.loadOBJ(mesh, "data/meshes/sphere2.obj");

        // Create test texture
        GLsizei texSize = 256;
        vector<GLubyte> textureData;
        for (int j = 0; j < texSize; j++) {
            for (int i = 0; i < texSize; i++) {
                float x = cos(2 * M_PI / texSize * i) / 2.0f + 0.5f;
                float y = sin(2 * M_PI / texSize * j);
                textureData.push_back((GLubyte)((x*y*y)*255.0f));
            }
        }
        glGenTextures(1, &testTexture);
        glBindTexture(GL_TEXTURE_2D, testTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, texSize, texSize, 0,
                GL_RED, GL_UNSIGNED_BYTE, &textureData[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glGenSamplers(1, &testTexSampler);
        glSamplerParameteri(testTexSampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glSamplerParameteri(testTexSampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glSamplerParameteri(testTexSampler, GL_TEXTURE_WRAP_S, GL_REPEAT);

        // Create the entity tree
        sun = new Entity();
//        object1 = new Entity(&mesh1);
//        object1->setPosition(vec3(-1, -0.75f, -2));
//        object1->rotateDeg(vec3(1, 0, 0), 45);
//        object2 = new Entity(&mesh1);
//        object2->setPosition(vec3(1.5f, 0, -0.5f));
//        object2->rotateDeg(vec3(0, 1, 0), 45);
        object3 = new Entity(&mesh);
        object3->setPosition(vec3(0, 0, -2));
//        object1->addChild(object2);
//        object1->addChild(object3);
//        sun->addChild(object1);
        sun->addChild(object3);
        setRoot(sun);

        // Grab the mouse to control the camera
        grabMouse();
    }

    void update(double delta) {
        float speed = 0.025;
        float rotspeed = 0.0025;
        float scrollrotspeed = 0.1;
        if (keyPressed(GLFW_KEY_W)) {
            //            cout << "W" << endl;
            getCamera().moveRelative(0, 0, -speed);
        }
        if (keyPressed(GLFW_KEY_S)) {
            //            cout << "S" << endl;
            getCamera().moveRelative(0, 0, speed);
        }
        if (keyPressed(GLFW_KEY_A)) {
            //            cout << "A" << endl;
            getCamera().moveRelative(-speed, 0, 0);
        }
        if (keyPressed(GLFW_KEY_D)) {
            //            cout << "D" << endl;
            getCamera().moveRelative(speed, 0, 0);
        }
        if (keyPressed(GLFW_KEY_Q)) {
            //            cout << "Q" << endl;
            getCamera().moveRelative(0, speed, 0);
        }
        if (keyPressed(GLFW_KEY_E)) {
            //            cout << "E" << endl;
            getCamera().moveRelative(0, -speed, 0);
        }
        if (keyPressed(GLFW_KEY_Z)) {
            //            cout << "Z" << endl;
            getCamera().moveRelative(0, -speed, 0);
        }
        if (keyPressed(GLFW_KEY_UP)) {
            //            cout << "Up" << endl;
            getCamera().tilt(rotspeed * 1);
        }
        if (keyPressed(GLFW_KEY_DOWN)) {
            //            cout << "Down" << endl;
            getCamera().tilt(rotspeed * -1);
        }
        if (keyPressed(GLFW_KEY_LEFT)) {
            //            cout << "Left" << endl;
            getCamera().pan(rotspeed * -1);
        }
        if (keyPressed(GLFW_KEY_RIGHT)) {
            //            cout << "Right" << endl;
            getCamera().pan(rotspeed * 1);
        }
        double dx, dy;
        getMouseMotion(&dx, &dy);
        getCamera().pan(rotspeed * dx);
        getCamera().tilt(rotspeed * -dy);
        getCamera().roll(scrollrotspeed * getScrollDY());
    }

    void renderWorld(mat4 base) {
        vec4 sunCameraPosition = base * vec4(0, 0, 0, 1);
        setSunPosition(sp1, sunCameraPosition);
        setSunPosition(sp2, sunCameraPosition);
        glActiveTexture(GL_TEXTURE0 + testTexUnit);
        glBindTexture(GL_TEXTURE_2D, testTexture);
        glBindSampler(testTexUnit, testTexSampler);
    }

    void renderHUD(mat4 base) {
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindSampler(testTexUnit, 0);
    }

    void resized(int width, int height) {
        super::resized(width, height);
        setCameraToClipMatrix(sp1, getCamera());
        setCameraToClipMatrix(sp2, getCamera());
    }
};

int main() {
    int ok = initHeliocentric();
    if (!ok) {
        cerr << "Failed to initialize heliocentric" << endl;
        exit(EXIT_FAILURE);
    }

    int width, height;
    getCurrentResolution(&width, &height);
    cout << "Screen resolution: " << width << "x" << height << endl;

    Camera camera(0.001f, 100, 1);
    EngineTest game(800, 600, "test", true, false, camera);
    game.run();

    exitHeliocentric();
    return 0;
}