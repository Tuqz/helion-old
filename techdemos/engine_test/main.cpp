#include "heliocentric/hcgame3d.hpp"
#include "heliocentric/shaders.hpp"
#include "heliocentric/mesh.hpp"
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

class EngineTest : public HcGame3D {
private:
    GLuint program, vao;
    GLuint modelToCameraUniform, cameraToClipUniform, sunPositionUniform;
    Mesh mesh;

public:
    EngineTest(int width, int height, string title, bool resizable,
            bool fullscreen, Camera& camera)
            : HcGame3D(width, height, title, resizable, fullscreen, camera) {
    }

    void init() {
        glfwPollEvents();
        super::init();

        // Load the mesh
        mesh.load("data/meshes/cube.obj");

        // Create shader program
        ShaderProgram sp("data/shaders/simple.vert", "data/shaders/simple.frag");
        program = sp.getProgram();
        // Transform matrix uniforms
        modelToCameraUniform = sp.getUniformLocation("modelToCameraMatrix");
        cameraToClipUniform = sp.getUniformLocation("cameraToClipMatrix");
        // Lighting uniforms
        sunPositionUniform = sp.getUniformLocation("sunPosition");
        glUseProgram(program);
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
        glUseProgram(program);

        vec4 sunCameraPosition = base * vec4(0, 0, 0, 1);
        glUniform3f(sunPositionUniform, sunCameraPosition.x, sunCameraPosition.y, sunCameraPosition.z);
        glUniformMatrix4fv(modelToCameraUniform, 1, GL_FALSE, glm::value_ptr(glm::translate(base, vec3(-1, 0, -2))));

        mesh.render();

        glUseProgram(0);
    }

    void renderHUD(mat4 base) {
    }

    void resized(int width, int height) {
        super::resized(width, height);
        glUseProgram(program);
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