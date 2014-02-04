#include "heliocentric/hcgame3d.hpp"
#include <iostream>

using namespace std;

class EngineTest : public HcGame3D {
private:
	bool print = true;
	GLuint vao, vbo;
public:

	EngineTest(int width, int height, string title, bool resizable, Camera& camera)
			: HcGame3D(width, height, title, resizable, camera) {
		//		cout << "Constructor of EngineTest" << endl;
	}

	void init() {
		HcGame3D::init();
		float vertexData[] = {
			0.25f, 0.25f, -1.25f, 1.0f,
			0.25f, -0.25f, -1.25f, 1.0f,
			-0.25f, 0.25f, -1.25f, 1.0f,

			0.25f, -0.25f, -1.25f, 1.0f,
			-0.25f, -0.25f, -1.25f, 1.0f,
			-0.25f, 0.25f, -1.25f, 1.0f,

			0.25f, 0.25f, -2.75f, 1.0f,
			-0.25f, 0.25f, -2.75f, 1.0f,
			0.25f, -0.25f, -2.75f, 1.0f,

			0.25f, -0.25f, -2.75f, 1.0f,
			-0.25f, 0.25f, -2.75f, 1.0f,
			-0.25f, -0.25f, -2.75f, 1.0f,

			-0.25f, 0.25f, -1.25f, 1.0f,
			-0.25f, -0.25f, -1.25f, 1.0f,
			-0.25f, -0.25f, -2.75f, 1.0f,

			-0.25f, 0.25f, -1.25f, 1.0f,
			-0.25f, -0.25f, -2.75f, 1.0f,
			-0.25f, 0.25f, -2.75f, 1.0f,

			0.25f, 0.25f, -1.25f, 1.0f,
			0.25f, -0.25f, -2.75f, 1.0f,
			0.25f, -0.25f, -1.25f, 1.0f,

			0.25f, 0.25f, -1.25f, 1.0f,
			0.25f, 0.25f, -2.75f, 1.0f,
			0.25f, -0.25f, -2.75f, 1.0f,

			0.25f, 0.25f, -2.75f, 1.0f,
			0.25f, 0.25f, -1.25f, 1.0f,
			-0.25f, 0.25f, -1.25f, 1.0f,

			0.25f, 0.25f, -2.75f, 1.0f,
			-0.25f, 0.25f, -1.25f, 1.0f,
			-0.25f, 0.25f, -2.75f, 1.0f,

			0.25f, -0.25f, -2.75f, 1.0f,
			-0.25f, -0.25f, -1.25f, 1.0f,
			0.25f, -0.25f, -1.25f, 1.0f,

			0.25f, -0.25f, -2.75f, 1.0f,
			-0.25f, -0.25f, -2.75f, 1.0f,
			-0.25f, -0.25f, -1.25f, 1.0f
		};
		
		glGenBuffers(1, &vbo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void update(double delta) {
		//		cout << "update() of EngineTest" << endl;
	}

	void renderWorld(mat4 base) {
		if (print) {
			const float *values = (const float*) glm::value_ptr(base);
			for (int r = 0; r < 4; ++r) {
				for (int c = 0; c < 4; ++c) {
					cout << values[r + 4 * c] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		print = false;
	}

	void renderHUD(mat4 base) {

	}
};

int main() {
	initHeliocentric();

	Camera camera(0.001f, 100, 1);
	EngineTest game(800, 600, "test", false, camera);
	game.run();

	exitHeliocentric();
	return 0;
}
