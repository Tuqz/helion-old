#include "heliocentric/hcgame.hpp"
#include <iostream>

using namespace std;

class EngineTest : public HCGame {
public:

	EngineTest(int width, int height, string title, bool resizable)
			: HCGame(width, height, title, resizable) {
		cout << "Constructor of EngineTest" << endl;
	}

	void init() {
		cout << "init() of EngineTest" << endl;
	}

	void update(double delta) {
		cout << "update() of EngineTest" << endl;
	}

	void render() {
		cout << "render() of EngineTest" << endl;
	}

	void closed() {
		cout << "closed() of EngineTest" << endl;
	}
};

int main() {
	initHeliocentric();

	EngineTest game(800, 600, "test", true);
	game.run();

	exitHeliocentric();
	return 0;
}
