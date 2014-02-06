#include "heliocentric/hcgame3d.hpp"
#include "heliocentric/shaders.hpp"
#include <glm/gtc/matrix_transform.hpp> 
#include <iostream>

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

class EngineTest : public HcGame3D {
private:
	bool print = true;
	GLuint program, vao, vbo;
	GLuint modelToCameraUniform, cameraToClipUniform;
public:

	EngineTest(int width, int height, string title, bool resizable, Camera& camera)
			: HcGame3D(width, height, title, resizable, camera) {
	}

	void init() {
		super::init();
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
			-0.25f, -0.25f, -1.25f, 1.0f,

			0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f,

			0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f,

			0.8f, 0.8f, 0.8f, 1.0f,
			0.8f, 0.8f, 0.8f, 1.0f,
			0.8f, 0.8f, 0.8f, 1.0f,

			0.8f, 0.8f, 0.8f, 1.0f,
			0.8f, 0.8f, 0.8f, 1.0f,
			0.8f, 0.8f, 0.8f, 1.0f,

			0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f,

			0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f,

			0.5f, 0.5f, 0.0f, 1.0f,
			0.5f, 0.5f, 0.0f, 1.0f,
			0.5f, 0.5f, 0.0f, 1.0f,

			0.5f, 0.5f, 0.0f, 1.0f,
			0.5f, 0.5f, 0.0f, 1.0f,
			0.5f, 0.5f, 0.0f, 1.0f,

			1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 0.0f, 1.0f,

			1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 0.0f, 1.0f,

			0.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 1.0f, 1.0f,

			0.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 1.0f, 1.0f,

		};

		ShaderProgram sp("data/shaders/simple.vert", "data/shaders/simple.frag");
		program = sp.getProgram();
		modelToCameraUniform = sp.getUniformLocation("modelToCameraMatrix");
		cameraToClipUniform = sp.getUniformLocation("cameraToClipMatrix");

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof (vertexData), vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
	}

	void update(double delta) {
	}

	void renderWorld(mat4 base) {
		if (print) {
			cout << "World-to-camera matrix:" << endl;
			printMatrix(glm::translate(base, vec3(-0.5, 0.5, 0)));
			cout << "Camera-to-clip matrix:" << endl;
			printMatrix(getCamera().getCameraToClipMatrix());
		}
		print = false;

		glUseProgram(program);

		glUniformMatrix4fv(modelToCameraUniform, 1, GL_FALSE, glm::value_ptr(glm::translate(base, vec3(-0.5, 0.5, 0))));
		glUniformMatrix4fv(cameraToClipUniform, 1, GL_FALSE, glm::value_ptr(getCamera().getCameraToClipMatrix()));
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)(36 * 4 * sizeof(float)));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glUseProgram(0);
	}

	void renderHUD(mat4 base) {
	}
};

int main() {
	initHeliocentric();

	Camera camera(0.001f, 100, 1);
	EngineTest game(800, 600, "test", true, camera);
	game.run();

	exitHeliocentric();
	return 0;
}
