#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Graph.h"

int main(int argc, char* argv[])
{
	std::string filePath = argv[1];

	std::ifstream file;
	file.open(filePath);
	std::vector< std::vector <bool> > map;
	std::string value;
	size_t rows = 0;

	std::vector<Node> groupNames;
	std::vector<Node> people;

	while (file.good())
	{
		std::getline(file, value, '\n');
		//std::cout << value << "\n";
		map.resize(rows + 1);

		//Reading Group names:
		if (rows == 0)
		{
			for (size_t i = 0; i < value.length(); i++)
			{
				if (value[i] != ',' && value[i] != ';')
				{
					int count = i;
					char temp[64];

					while (value[count] != ',' && value[count] != ';')
					{
						if (count - i < 63)
							temp[count - i] = value[count];
						count++;
					}

					Node tempNode;
					tempNode.setName(temp);
					groupNames.push_back(tempNode);
				}
			}

		}

		for (size_t i = 0; i < value.length(); i++)
		{
			if (value[i] != ',' && value[i] != ';')
			{
				if (isdigit(value[i]))
				{
					if(value[i] == '0')
						map[rows].push_back(false);
					else
						map[rows].push_back(true);

				}
				else //if it's not digit it's a name:
				{
					int count = i;
					char temp[64];

					while (value[count] != ',' && value[count] != ';')
					{
						if (count - i < 63)
							temp[count - i] = value[count];
						count++;
					}

					Node tempNode;
					tempNode.setName(temp);
					people.push_back(tempNode);
				}

				
			}
		}

		rows++;
	}

	//test:

	for (size_t i = 0; i < map.size(); i++)
	{
		for (size_t j = 0; j < map[0].size(); j++)
		{
			std::cout << "{" << map[i][j] << "}";
		}
		std::cout << std::endl;
	}

	
	return 0;
}