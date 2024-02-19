#pragma once
#include <string>

class Shaders
{
	public:
	static std::string GetVertexShader();
	static std::string GetFragmentShader();

	 //function to create a glfw shader program
static unsigned int CreateShader();
};

