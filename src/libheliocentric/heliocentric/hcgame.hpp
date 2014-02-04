#include <GLFW/glfw3.h>
#include <string>

class HcGame {
private:
	std::string title;
	double prevTime, prevCalcTime;
	int fps;
	GLFWwindow* window;
public:
	HcGame(int width, int height, std::string title, bool resizable);
	// Game loop management
	void run();
	void shutdown();
	virtual bool shouldStop();
	// Display management
	virtual void closed();
	virtual void resized();
	virtual void resized(int width, int height);
	void setDisplayMode();
	void setTitle(std::string title);
	std::string getTitle();
	// Time management
	double getTime();
	double getDelta();
protected:
	// Implementation-specific parts
	virtual void init() = 0;
	virtual void update(double delta) = 0;
	virtual void render() = 0;
	// Callback
private:
	void updateFPS();
};

int initHeliocentric();
void exitHeliocentric();
bool glversion(int major, int minor);
