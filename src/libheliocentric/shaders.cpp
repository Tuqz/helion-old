#include "heliocentric/core.hpp"
#include "heliocentric/shaders.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>

using namespace std;

string getName(int shaderType) {
	if (shaderType == GL_VERTEX_SHADER) {
		return "vertex";
	}
	if (shaderType == GL_GEOMETRY_SHADER) {
		return "geometry";
	}
	if (shaderType == GL_FRAGMENT_SHADER) {
		return "fragment";
	}
	return "<unknown type>";
}

string loadShader(string fname) {
	ifstream t(fname, ifstream::in);
	string str;

	t.seekg(0, ios::end);
	str.reserve(t.tellg());
	t.seekg(0, ios::beg);

	str.assign((istreambuf_iterator<char>(t)),
			istreambuf_iterator<char>());
	return str;
}

int createShader(int shaderType, string filename) {
	// Create the actual shader
	int shader = glCreateShader(shaderType);
	string shaderSource = loadShader(filename);
	const char *c_str = shaderSource.c_str();
	glShaderSource(shader, 1, &c_str, NULL);
	glCompileShader(shader);

	// Error handling
	int status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		int logLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		char log[logLength];
		glGetShaderInfoLog(shader, logLength, &logLength, log);
		cout << "Failure in compiling " << getName(shaderType) << " shader. "
				<< "Error log:\n" << log << endl;
		exit(1);
	}

	// Return the shader upon success
	return shader;
}

ShaderProgram::ShaderProgram(string vertexShader, string fragmentShader)
		: ShaderProgram(vertexShader, "", fragmentShader) {
}

ShaderProgram::ShaderProgram(string vertexShader, string geometryShader, string fragmentShader) {
	// Create the shaders
	int vs = createShader(GL_VERTEX_SHADER, vertexShader);
	int gs = -1;
	if (geometryShader.compare("")) {
		createShader(GL_GEOMETRY_SHADER, geometryShader);
	}
	int fs = createShader(GL_FRAGMENT_SHADER, fragmentShader);

	// Create the program
	program = glCreateProgram();

	// Attach the shaders
	glAttachShader(program, vs);
	if (gs != -1) {
		glAttachShader(program, gs);
	}
	glAttachShader(program, fs);

	// Bind the shader attributes TODO: REQUIRED FOR OPENGL < 3.3
	//	if (attributes != null) {
	//		for (int i : attributes.keySet()) {
	//			glBindAttribLocation(program, i, attributes.get(i));
	//		}
	//	}

	// Link the Program
	glLinkProgram(program);

	// Error handling
	int status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		int logLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
		char log[logLength];
		glGetProgramInfoLog(program, logLength, &logLength, log);
		cout << "Failure in linking program. Error log:\n" << log << endl;
	}

	// Clean up
	glDetachShader(program, vs);
	if (gs != -1) {
		glDetachShader(program, gs);
	}
	glDetachShader(program, fs);

	glDeleteShader(vs);
	if (gs != -1) {
		glDeleteShader(gs);
	}
	glDeleteShader(fs);
}

GLuint ShaderProgram::getProgram() {
	return program;
}

GLint ShaderProgram::getUniformLocation(string name) {
	return glGetUniformLocation(program, name.c_str());
}

GLuint ShaderProgram::getUniformBlockIndex(string name) {
	return glGetUniformBlockIndex(program, name.c_str());
}

void ShaderProgram::destroy() {
	glDeleteProgram(program);
}