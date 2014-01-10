#include <iostream>
#include <string>
#include <helion/mesh.h>
#include <GLFW/glfw3.h>

// Needed for thread management
#include <thread>
#include <chrono>


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

int main(int argc, char** argv) {
	int choices[3];
	std::cout<<"If you want: a pointed cockpit, enter 1; a rounded cockpit, enter 2 or for a flat cockpit, enter 3\n";
	std::cin >> choices[0];
	std::cout<<"If you want: a tall thin fuel tank, enter 1; a short fat fuel tank, enter 2 or a toroidal fuel tank, enter 3\n";
	std::cin >> choices[1];
	std::cout<<"If you want: a standard size engine, enter 1; a large size engine, enter 2 or a jet engine, enter 3\n";
	std::cin >> choices[2];

	std::string filenames[] = {"pointed", "rounded", "flat", "tall", "short", "toroidal", "standard", "fat", "jet"};

	// Find path to binary to detect if we were launched from a different directory
	// And then use that path assuming the binary is in the correct place (next to data/).
	char* cpath = argv[0];
	int n=0;
	for(int i=0; cpath[i]!='\0'; i++){
		if (cpath[i]=='/') n=i;
	}
	std::string path;
	if(n>0){
		cpath[n]='\0';
		path = cpath;
	}else{
		path = ".";
	}

	render::Mesh rocket[3];
	double scale = 0;
	for(int i = 0; i < 3; ++i) {
		if(!rocket[i].load(""+path+"/data/"+(filenames[(i*3)+choices[i]-1])+".obj")) {
			std::cout<<"Error! Files not loaded correctly.\n";
			return 1;
		}
		scale += rocket[i].height();
	}
	scale = 2/scale;

	// Attempt to initialize GLFW
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	// Set any hits we need for our windows
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);

	// Windowed mode, no parent window
	GLFWwindow* root = glfwCreateWindow(800, 600, "Rocket Designer", NULL, NULL);
	if (!root) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Don't forget to make context current *before* drawing anything! ;)
	glfwMakeContextCurrent(root);
	glfwSetKeyCallback(root, key_callback);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	while(!glfwWindowShouldClose(root)) {
		// Don't rape the CPU - ~60Hz (we should really be updating on vsync)
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		glClear(GL_COLOR_BUFFER_BIT);

		double shift = 0;
		for(int i=2; i>=0; i--) {
			rocket[i].render(scale, {0, -1+shift, 0});
			shift += scale*rocket[i].height();
		}

		glfwSwapBuffers(root);
		glfwPollEvents();
	}
	return 0;
}
