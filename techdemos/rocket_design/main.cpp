#include <iostream>
#include <string>
#include "../../src/mesh.h"
#include <GL/glfw.h>

int main() {
	int choices[3];
	std::cout<<"If you want: a pointed cockpit, enter 1; a rounded cockpit, enter 2 or for a flat cockpit, enter 3\n";
	std::cin >> choices[0];
	std::cout<<"If you want: a tall thin fuel tank, enter 1; a short fat fuel tank, enter 2 or a toroidal fuel tank, enter 3\n";
	std::cin >> choices[1];
	std::cout<<"If you want: a standard size engine, enter 1; a large size engine, enter 2 or a jet engine, enter 3\n";
	std::cin >> choices[2];
	
	std::string filenames[] = {"pointed", "rounded", "flat", "tall", "short", "toroidal", "standard", "fat", "jet"};

	render::Mesh rocket[3];
	double height = 0;
	for(int i = 0; i < 3; ++i) {
		if(!rocket[i].load("data/"+(filenames[(i*3)+choices[i]-1])+".obj")) {
			std::cout<<"Error! Files not loaded correctly.\n";
			return 1;
		}
		height += rocket[i].height();
	}

	glfwInit();
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
	glfwOpenWindow(800, 600, 0, 0, 0, 0, 32, 0, GLFW_WINDOW);
	glfwSetWindowTitle("Rocket viewer");
	
	while(glfwGetWindowParam(GLFW_OPENED)) {
		for(int i = 0; i < 3; ++i) {
			int i = 0;
			double shift = 0;
			for(int j = 0; j < i; ++j) {
				shift += rocket[j].height();
			}
			rocket[i].render(2/height, {0, 1 - 0.5*(shift/height) - 0.5*(rocket[i].height()/height), 0});
		}
		glfwSwapBuffers();
	}
	return 0;
}
