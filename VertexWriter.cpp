#include "VertexWriter.h"

#include <fstream>
#include <iostream>
#include <ostream>

void VertexWriter::WriteVertexData(std::string Path, std::vector<Vertex> Vertices, bool Append)
{
	//open the file
	std::ofstream File;

	//check whether or not we should append to the file or not
	if (Append)
	{
		File.open(Path, std::ios::app);
	}
	else
	{
		File.open(Path, std::ios::out | std::ios::trunc);	
	}

	//check if opening the file was successful
	if (File.is_open())
	{
		//write first line
		File << "Vertices: " << Vertices.size() << std::endl;

		//iterate through each vertex
		for (const auto & LocVertex : Vertices)
		{
			//write the vertex's data to the file
			File << LocVertex.Pos.x << "	" << LocVertex.Pos.y << "	" << LocVertex.Pos.z << "	" << LocVertex.RGB.r << "	" << LocVertex.RGB.g << "	" << LocVertex.RGB.b << "	" << std::endl;
		}
	}
	else
	{
		//print an error message
		std::cout << "Error: Could not open file " << Path << std::endl;
	}

	//close the file
	File.close();
}

std::vector<Vertex> VertexWriter::WriteVertexDataFromFunc(float(* VertexFunction)(float Param), const int StartIndex, const int LastIndex, const int LevelOfDetail)
{
	//vector to store the vertices
	std::vector<Vertex> Vertices;

	//iterate through each index
	for (int LocIndex = StartIndex; LocIndex < (LastIndex * LevelOfDetail) + 1; LocIndex += 1)
	{
		//colour of the vertex
		glm::vec3 LocColor = glm::vec3(1.0f, 1.0f, 1.0f);

		//get the mathematical function's output for the current index
		const float LocOutput = VertexFunction(float(LocIndex) / float(LevelOfDetail));

		//get the mathematical function's output for the next index
		const float LocNextOutput = VertexFunction(float(LocIndex + 1) / float(LevelOfDetail));

		//get the mathematical function's output for the previous index
		const float LocPrevOutput = VertexFunction(float(LocIndex - 1) / float(LevelOfDetail));

		//check if the current output is either the highest or lowest output
		if (LocOutput > LocNextOutput && LocOutput > LocPrevOutput || LocOutput < LocNextOutput && LocOutput < LocPrevOutput)
		{
			//set the colour to yellow
			LocColor = glm::vec3(1.0f, 1.0f, 0.0f);
		}
		//check if the output is currently growing (greater than the last output)
		else if (LocOutput > LocPrevOutput)
		{
			//set the colour to green
			LocColor = glm::vec3(0.0f, 1.0f, 0.0f);
		}
		//check if the output is currently shrinking (less than the last output)
		else if (LocOutput < LocPrevOutput)
		{
			//set the colour to red
			LocColor = glm::vec3(1.0f, 0.0f, 0.0f);
		}

		//create a vertex from the coordinates and colour
		Vertex CurrentVertex = Vertex(glm::vec3(float(LocIndex) / float(LevelOfDetail), LocOutput, 0.0f), LocColor);

		//add the vertex to the vector
		Vertices.push_back(CurrentVertex);

		////print the vertex
		//std::cout << CurrentVertex.Pos.x << "	" << CurrentVertex.Pos.y << "	" << CurrentVertex.Pos.z << "	" << CurrentVertex.RGB.r << "	" << CurrentVertex.RGB.g << "	" << CurrentVertex.RGB.b << std::endl;
	}

	return Vertices;
}

std::vector<float> VertexWriter::ConvertVertexDataToFloats(std::vector<Vertex> Vertices)
{
	//vector to store the floats
	std::vector<float> Floats;

	//iterate through each vertex
	for (const auto & LocVertex : Vertices)
	{
		//add the vertex's data to the vector
		Floats.push_back(LocVertex.Pos.x / 10);
		Floats.push_back(LocVertex.Pos.y / 10);
		Floats.push_back(LocVertex.Pos.z);
		Floats.push_back(LocVertex.RGB.r);
		Floats.push_back(LocVertex.RGB.g);
		Floats.push_back(LocVertex.RGB.b);
	}

	return Floats;
}
