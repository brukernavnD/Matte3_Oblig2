#include "VertexLoader.h"

std::vector<Vertex> VertexLoader::LoadVertexData(std::string Path)
{
	//create a file stream
	std::ifstream file;
	std::stringstream ss;
	std::string line;

	//create a vector to store the vertex data
	std::vector<Vertex> VertexData;

	//variable to store tokens
	std::string s;

	//open the file
	file.open(Path);

	//check if the file is open
	if (!file.is_open())
	{
		std::cout << "Failed to open file" << std::endl;
		return {};
	}

	//iterate through each line of the file
	while (std::getline(file, line))
	{
		//skip the first line
		if (line.find("Vertices:") == 0)
		{
			continue;
		}

		//create a string stream from the line
		std::stringstream ss2 = std::stringstream(line);

		//vector to store the tokens
		std::vector<float> tokens;

		//iterate through each token of the line
		while (getline(ss2, s, '	')) {
 
	        // store token string in the vector
	        tokens.push_back(std::stof(s));
		}

		//create a vertex from the tokens
		Vertex CurrentVertex = Vertex(glm::vec3(tokens.at(0), tokens.at(1), tokens.at(2)), glm::vec3(tokens.at(3), tokens.at(4), tokens.at(5)));

		//add the vertex to the vector
		VertexData.push_back(CurrentVertex);

		////print the vertex
		//std::cout << CurrentVertex.Pos.x << "	" << CurrentVertex.Pos.y << "	" << CurrentVertex.Pos.z << "	" << CurrentVertex.RGB.r << "	" << CurrentVertex.RGB.g << "	" << CurrentVertex.RGB.b << std::endl;
	}

	//close the file
	file.close();

	//return the vertex data
	return VertexData;
}
