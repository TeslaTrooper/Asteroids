#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include <GL/glew.h>
#include <iostream>

/*
Diese Klasse stellt zwei Shader bereit und erlaubt es, aus diesen Shadern
ein fertiges Shader Program zu erzeugen.
*/
class ShaderProgram {

	void compileShader(GLuint shader, const GLchar* shaderSource);

	GLuint createShader(GLenum shaderType, const GLchar* shaderSource);

	char* readShaderFile(char* file);

public:
	ShaderProgram();
	~ShaderProgram();

	/*
	Erzeugt aus den zwei Shadern ein fertiges Shader Program.
	@return Gibt die von OpenGL erzeugte ID zu diesem Program zurück.
	*/
	GLuint createShaderProgram();

};

#endif SHADER_PROGRAM