#include <string>

using namespace std;

class ShaderProgram {
private:
	int program;
public:
	ShaderProgram(string vertexShader, string fragmentShader);
	ShaderProgram(string vertexShader, string geometryShader, string fragmentShader);
	GLuint getProgram();
	GLint getUniformLocation(string name);
	GLuint getUniformBlockIndex(string name);
	void destroy();
};

