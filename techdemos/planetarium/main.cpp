#include <helion/bodies.h>
#include <helion/render.h>
#include <helion/camera.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Needed for thread management
#include <thread>
#include <chrono>

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

int main() {

	/* Attempt to initialize GLFW */
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	/* Old GLFW2 code */
#if 0
	glfwCreateWindow(800, 600, 0, 0, 0, 0, 32, 0, NULL);
	glfwSetWindowTitle("Planetarium");
	glfwEnable(GLFW_STICKY_KEYS);
#endif // 0

	/* Set any hits we need for our windows */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);

	/* Windowed mode, no parent window */
	GLFWwindow* root = glfwCreateWindow(800, 600, "Planetarium", NULL, NULL);
	if (!root) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	/* Make the context current */
	glfwMakeContextCurrent(root);
	glfwSetKeyCallback(root, key_callback);

	glClearColor(0, 0, 0, 0);

	render::Camera cam = {{0, 0.5, 0}, {0, 0, 0}, {1, 0, 0}};
	cam.refresh();

	while(glfwGetKey(root, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        !glfwWindowShouldClose(root)) {

        /* Don't rape the CPU - ~60Hz (we should really be updating on vsync) */
		std::this_thread::sleep_for(std::chrono::milliseconds(16));

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		double scale = (5E-12)/1.5;
		double deltat = 200000.0/6.0;
		render::planet_render(sim::Sun, scale);
		render::planet_render(sim::Mercury, scale);
		render::planet_render(sim::Venus, scale);
		render::planet_render(sim::Earth, scale);
		render::planet_render(sim::Moon, scale);
		render::planet_render(sim::Mars, scale);
		render::orbit_render(sim::Mercury, scale);
		render::orbit_render(sim::Venus, scale);
		render::orbit_render(sim::Earth, scale);
		render::orbit_render(sim::Mars, scale);
		sim::Venus.update(deltat);
		sim::Mercury.update(deltat);
		sim::Earth.update(deltat);
		sim::Moon.update(deltat);
		sim::Mars.update(deltat);
		glfwSwapBuffers(root);
		glfwPollEvents();
	}
	return 0;
}
