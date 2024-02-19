#include "Shaders.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "glad/glad.h"

std::string Shaders::GetVertexShader()
{
	//storage for the vertex shader
	std::ifstream VertexShaderFile;
	std::stringstream VertexShaderStream;

	//open the file
	VertexShaderFile.open("VertexShaderSource.shadersourcecode");

	//read the file's buffer contents into streams
	VertexShaderStream << VertexShaderFile.rdbuf();

	//close the file
	VertexShaderFile.close();

	//convert the stream into a string
	std::string VertexShaderString = VertexShaderStream.str();

	////print the string
	//std::cout << VertexShaderString << std::endl;

	//return the string
	return VertexShaderString;
}

std::string Shaders::GetFragmentShader()
{
	//storage for the fragment shader
	std::ifstream FragmentShaderFile;
	std::stringstream FragmentShaderStream;

	//open the file
	FragmentShaderFile.open("FragmentShaderSource.shadersourcecode");

	//read the file's buffer contents into streams
	FragmentShaderStream << FragmentShaderFile.rdbuf();

	//close the file
	FragmentShaderFile.close();

	//convert the stream into a string
	std::string FragmentShaderString = FragmentShaderStream.str();

	////print the string
	//std::cout << FragmentShaderString << std::endl;

	//return the string
	return FragmentShaderString;
}

unsigned Shaders::CreateShader()
{
	//storage variables for converting the strings to const char**
	const std::string A = GetVertexShader();
	const std::string B = GetFragmentShader();
	const char *C_str1 = A.c_str();
	const char *C_str2 = B.c_str();

	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
   
	glShaderSource(vertexShader, 1, &C_str1, NULL);
	glCompileShader(vertexShader);

	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &C_str2, NULL);
	glCompileShader(fragmentShader);

	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// link shaders
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	return shaderProgram;
}
