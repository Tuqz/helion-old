#include <string>

using namespace std;

class ShaderProgram {
private:
	int program;
public:
	ShaderProgram(string vertexShader, string fragmentShader);
	ShaderProgram(string vertexShader, string geometryShader, string fragmentShader);
	int getProgram();
	int getUniformLocation(string name);
	int getUniformBlockIndex(string name);
	void destroy();
};

