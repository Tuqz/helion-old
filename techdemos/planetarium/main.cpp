#include "../../src/bodies.h"
#include "../../src/render.h"
#include <GL/glfw.h>
#include <iostream>

int main() {
	/*glfwInit();
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);

	glfwOpenWindow(800, 600, 0, 0, 0, 0, 32, 0, GLFW_WINDOW);
	glfwSetWindowTitle("test");
	glfwEnable(GLFW_STICKY_KEYS);
	while(glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS && glfwGetWindowParam(GLFW_OPENED)) {
		double scale = 6.6666666666666E-12;
		render::planet_render(sim::Earth, scale);
		sim::Earth.update(100.0/6.0);
		glfwSwapBuffers();
	} 
	*/
	sim::Body foo = {{0, 0, 0}, 0, 0, 0, 0, 0, 0, "foo", "bar", foo, false};
	foo.assign(sim::Earth);
	std::cout<<foo.name<<"\n";
	foo.assign(sim::Moon);
	std::cout<<foo.name<<"\n";
	return 0;
}
