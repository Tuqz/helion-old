#include <GLFW/glfw3.h>
#include <helion/bodies.h>
#include <helion/body.h>
#include <helion/ship.h>
#include <helion/part.h>
#include <helion/render.h>
#include <helion/camera.h>
#include <iostream>
#include <vector>

#include <thread>
#include <chrono>

double deltat = 10.0;
struct keyboard_controller {
	sim::Ship ship;
	static keyboard_controller& getInstance() {
		static keyboard_controller instance;
		return instance;
	}
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		getInstance().key_callback_impl(window, key, action);
	}
	
	void key_callback_impl(GLFWwindow* window, int key, int action) {
		if(action == GLFW_PRESS) {
			switch (key) {
				case GLFW_KEY_ESCAPE:
					glfwSetWindowShouldClose(window, GL_TRUE);
					break;
				case GLFW_KEY_W:
					ship.rotation = ship.vel();
					ship.accel(10, deltat);
					break;
				default:
					break;
			}
		}
	}
};

int main() {
	sim::Body centre;
	centre = sim::Earth;
	centre.orbit.semimajor = 0;
	centre.central_mass = NULL;
	centre.Sun = true;
	
	std::vector<sim::Part> empty;

	sim::Ship ship = {&centre, {6371000, 0, 0}, empty, {1, 0, 0}, 0, 0, 0, 0};

	struct keyboard_controller controller = {ship};
	
	if(!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);

	GLFWwindow* root = glfwCreateWindow(800, 600, "Ship testing", NULL, NULL);
	
	if(!root) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(root);
	glfwSetKeyCallback(root, controller.key_callback);

	glClearColor(0, 0, 0, 0);

	while(glfwGetKey(root, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(root)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		double scale = 1.081E-8;

		render::planet_render(centre, scale);
		render::ship_render(controller.ship, scale);
		render::orbit_render(controller.ship, scale);

		controller.ship.update(deltat);

		glfwSwapBuffers(root);
		glfwPollEvents();
	}
	
	return 0;
}
