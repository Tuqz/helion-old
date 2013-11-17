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
	while(glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS && glfwGetWindowParam(GLFW_OPENED)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		double scale = (9.66667E-12)/1.5;
		double deltat = 100000.0/6.0;
		render::planet_render(sim::Sun, scale);
		render::planet_render(sim::Mercury, scale);
		sim::Mercury.update(deltat);
		glfwSwapBuffers();
	} 
	return 0;
}
