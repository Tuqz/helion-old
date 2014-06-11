#include "core.hpp"
#include <string>

class HcGame {
private:
	std::string title;
	double prevTime, prevCalcTime;
	int fps;
	GLFWwindow* window;
	double prev_x, prev_y;
//public:
	double scroll_dx, scroll_dy;
public:
	HcGame(int width, int height, std::string title, bool resizable, bool fullscreen);
	// Game loop management
	void run();
	void shutdown();
	virtual bool shouldStop();
	// Display management
	virtual void closed();
	void resized();
	virtual void resized(int width, int height);
	void getWindowSize(int* width, int* height);
	void setTitle(std::string title);
	std::string getTitle();
	// Time management
	double getTime();
	double getDelta();
	// Input handling
	bool keyPressed(int key);
	void setMousePosition(double x, double y);
	void getMousePosition(double* x, double* y);
	void getMouseMotion(double* dx, double* dy);
	float getScrollDX();
	float getScrollDY();
	void grabMouse();
	void releaseMouse();
	void setMouseGrabbed(bool grab);
	bool isMouseGrabbed();
protected:
	// Implementation-specific parts
	virtual void init() = 0;
	virtual void update(double delta) = 0;
	virtual void render() = 0;
private:
	void updateFPS();
	friend void cb_scroll(GLFWwindow* window, double dx, double dy);
};

int initHeliocentric();
void exitHeliocentric();
bool glversion(int major, int minor);
void getCurrentResolution(int* width, int* height);