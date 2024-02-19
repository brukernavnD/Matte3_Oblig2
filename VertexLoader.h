#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>

#include "Vertex.h"

class VertexLoader
{
public:

	//function to load vertex data from a file
	static std::vector<Vertex> LoadVertexData(std::string Path);
};

