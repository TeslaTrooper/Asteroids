#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() {}

GLuint ShaderProgram::createShaderProgram() const {
	char* vertexShaderSource = readShaderFile("shader.vert");
	char* fragmentShaderSource = readShaderFile("shader.frag");

	GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
	GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLint success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success) {
		std::cout << "Error loading shader program!";
	}

	return shaderProgram;
}

void ShaderProgram::compileShader(const GLuint shader, const GLchar* shaderSource) const {
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		std::cout << "Error compiling shader!";
	}
}

GLuint ShaderProgram::createShader(const GLenum shaderType, const GLchar* shaderSource) const {
	GLuint shader = glCreateShader(shaderType);
	compileShader(shader, shaderSource);

	return shader;
}

char* ShaderProgram::readShaderFile(char const * const file) const {
	FILE *f = fopen(file, "rb");

	fseek(f, 0, SEEK_END);
	long lSize = ftell(f);
	rewind(f);

	char* data = new char[lSize];
	fread(data, lSize, 1, f);
	fclose(f);

	return data;
}

ShaderProgram::~ShaderProgram() {}