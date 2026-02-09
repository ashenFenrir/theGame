#include "Shader.hpp"

#include <exception>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include <glad/glad.h>

Shader::Shader(const char* vshaderPath, const char* fshaderPath)
{
	unsigned int vertexShader, fragmentShader, id;

	int  success;
	char infoLog[512];

	std::string vshaderCode;
	std::string fshaderCode;

	load_shader_code(vshaderPath, fshaderPath, vshaderCode, fshaderCode);

	const char *vertexShaderSource = vshaderCode.c_str();
	const char *fragmentShaderSource = fshaderCode.c_str();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s \n", infoLog);
	}


	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n %s \n", infoLog);
	}


	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);

	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n %s \n", infoLog);
	}
	glUseProgram(id);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader); 
}

Shader::~Shader()
{
	glDeleteProgram(id);
}

void Shader::load_shader_code(const char* vshaderPath, const char* fshaderPath, std::string& vcode, std::string& fcode)
{
	// Reading Files
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	try {
		vShaderFile.open(vshaderPath);
		fShaderFile.open(fshaderPath);
		std::stringstream vShaderStream, fShaderStream;
	
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
	
		vShaderFile.close();
		fShaderFile.close();
	
		vcode = vShaderStream.str();
		fcode = fShaderStream.str();
	}
	catch(std::ifstream::failure& e) {
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}


}