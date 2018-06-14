#pragma once

#include <string>
#include <GL/glew.h>

#include "Errors.h"

#include <fstream>
#include <vector>

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void compileShaders(const std::string&, const std::string&);

	void linkShaders();

private:
	GLuint programID;

	GLuint vertexShaderID;
	GLuint fragmentShaderID;

	void compileShader(const std::string&, GLuint);
};

