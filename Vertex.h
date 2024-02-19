#pragma once
#include <glm/vec3.hpp>

struct Vertex
{
	//our position
	glm::vec3 Pos = glm::vec3(0.0f, 0.0f, 0.0f);

	//our colour
	glm::vec3 RGB = glm::vec3(0.0f, 0.0f, 0.0f);

	//constructor(s)
	Vertex();
	Vertex(glm::vec3 InPos, glm::vec3 InRGB);
};

