#include "Shader.hpp"

#include <exception>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include <glad/glad.h>

Shader::Shader(const char* vshaderPath, const char* fshaderPath): ID(glCreateProgram())
{
	const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	int success;
	char infoLog[512];

	std::string vshaderCode;
	std::string fshaderCode;

	load_shader_code(vshaderPath, fshaderPath, vshaderCode, fshaderCode);

	const char *vertexShaderSource = vshaderCode.c_str();
	const char *fragmentShaderSource = fshaderCode.c_str();

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s \n", infoLog);
	}

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n %s \n", infoLog);
	}

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n %s \n", infoLog);
	}
	glUseProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader); 
}

Shader::~Shader()
{
	glDeleteProgram(ID);
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

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setUniform(const char* name, bool value)
{
	glUniform1i(glGetUniformLocation(ID, name), (int)value);
}

void Shader::setUniform(const char* name, int value)
{
	glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::setUniform(const char* name, float value)
{
	glUniform1f(glGetUniformLocation(ID, name), value);
}

void Shader::setUniform(const char* name, glm::vec2 value)
{
	glUniform2f(glGetUniformLocation(ID, name), value.x, value.y);
}

void Shader::setUniform(const char* name, glm::vec3 value)
{
	glUniform3f(glGetUniformLocation(ID, name), value.x, value.y, value.z);
}

void Shader::setUniform(const char* name, glm::vec4 value)
{
	glUniform4f(glGetUniformLocation(ID, name), value.x, value.y, value.z, value.w);
}

void Shader::setUniform(const char* name, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 4, GL_FALSE, glm::value_ptr(value));
}