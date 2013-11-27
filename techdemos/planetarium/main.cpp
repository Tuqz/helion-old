#include "../../src/bodies.h"
#include "../../src/render.h"
#include <GL/glfw.h>
#include <iostream>

int main() {
	glfwInit();
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
	glfwOpenWindow(800, 600, 0, 0, 0, 0, 32, 0, GLFW_WINDOW);
	glfwSetWindowTitle("Planetarium");
	glfwEnable(GLFW_STICKY_KEYS);
	glClearColor(0, 0, 0, 0);
	gluLookAt(0, 0.9, 0, 0, 0, 0, 0, 0, 1);
	while(glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS && glfwGetWindowParam(GLFW_OPENED)) {
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
		glfwSwapBuffers();
	} 
	return 0;
}
