#include "heliocentric/hcgame3d.hpp"
#include "heliocentric/shaders.hpp"
#include "heliocentric/mesh.hpp"
#include "heliocentric/entity.hpp"
#include "heliocentric/matrixstack.hpp"
#include <glm/gtc/matrix_transform.hpp> 
#include <iostream>
#include <unistd.h>

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

class TestEntity : public Entity {
private:
    Mesh& mesh;
    ShaderProgram sp;

public:

    TestEntity(Mesh& mesh, ShaderProgram sp) : mesh(mesh), sp(sp) {
    };

    virtual void update(double delta) {
    };

    void render(MatrixStack& ms) {
        glUseProgram(sp.getProgram());
        ms *= glm::translate(mat4(), position);
        glUniformMatrix4fv(sp.getUniformLocation("modelToCameraMatrix"), 1, GL_FALSE, ms.array());
        mesh.render();
        glUseProgram(0);
    };
};

class EngineTest : public HcGame3D {
private:
    ShaderProgram sp;
    GLuint vao;
    GLuint modelToCameraUniform, cameraToClipUniform, sunPositionUniform;
    Entity* sun;
    Entity* cube1;
    Entity* cube2;
    Mesh mesh;

public:

    EngineTest(int width, int height, string title, bool resizable,
            bool fullscreen, Camera& camera)
    : HcGame3D(width, height, title, resizable, fullscreen, camera), 
    sp("data/shaders/simple.vert", "data/shaders/simple.frag") {
    }

    ~EngineTest() {
        delete sun;
        delete cube1;
        delete cube2;
    }

    void init() {
        glfwPollEvents();
        super::init();

        // Transform matrix uniforms
        modelToCameraUniform = sp.getUniformLocation("modelToCameraMatrix");
        cameraToClipUniform = sp.getUniformLocation("cameraToClipMatrix");
        // Lighting uniforms
        sunPositionUniform = sp.getUniformLocation("sunPosition");
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

        // Create vertex array
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // Load the mesh
        mesh.load("data/meshes/cube.obj");

        // Create the entity tree
        sun = new Entity();
        cube1 = new TestEntity(mesh, sp);
        cube1->setPosition(vec3(-1, 0, -2));
        cube2 = new TestEntity(mesh, sp);
        cube2->setPosition(vec3(1.5f, 0, -0.5f));
        cube1->addChild(cube2);
        sun->addChild(cube1);
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
        glUseProgram(sp.getProgram());

        vec4 sunCameraPosition = base * vec4(0, 0, 0, 1);
        glUniform3f(sunPositionUniform, sunCameraPosition.x, sunCameraPosition.y, sunCameraPosition.z);
        
        glUseProgram(0);
    }

    void renderHUD(mat4 base) {
    }

    void resized(int width, int height) {
        super::resized(width, height);
        glUseProgram(sp.getProgram());
        glUniformMatrix4fv(cameraToClipUniform, 1, GL_FALSE, glm::value_ptr(getCamera().getCameraToClipMatrix()));
        glUseProgram(0);
    }
};

int main() {
    initHeliocentric();

    int width, height;
    getCurrentResolution(&width, &height);
    cout << "Screen resolution: " << width << "x" << height << endl;

    Camera camera(0.001f, 100, 1);
    EngineTest game(800, 600, "test", true, false, camera);
    game.run();

    exitHeliocentric();
    return 0;
}