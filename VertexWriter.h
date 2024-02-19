#pragma once
#include <string>
#include <vector>

#include "Vertex.h"

class VertexWriter
{
	public:

	//function to write vertex data to a file
	static void WriteVertexData(std::string Path, std::vector<Vertex> Vertices, bool Append = false);

	//function to write vertex data to a file from a mathematical function
	static std::vector<Vertex> WriteVertexDataFromFunc(float(* VertexFunction)(float Param), int StartIndex, int LastIndex, int LevelOfDetail);

	//function to convert a vector of vertices to a vector of floats
	static std::vector<float> ConvertVertexDataToFloats(std::vector<Vertex> Vertices);
};


