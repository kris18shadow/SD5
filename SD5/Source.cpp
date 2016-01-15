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
		//value.clear();
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
						if (count - i < 62)
							temp[count - i] = value[count];
						if (count < value.length())
							count++;
						else
							break;
					}

					temp[count - i] = '\0';

					Node* tempNode = new Node;
					tempNode->setName(temp);
					groupNames.push_back(*tempNode);

					i = count;
				}
			}

		}
		else
		{

			for (size_t i = 0; i < value.length(); i++)
			{
				if (value[i] != ',' && value[i] != ';')
				{
					if (isdigit(value[i]))
					{
						if (value[i] == '0')
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
							if (count - i < 62)
								temp[count - i] = value[count];
							if (count < value.length())
								count++;
						}

						temp[count - i] = '\0';

						Node* tempNode = new Node;
						tempNode->setName(temp);
						people.push_back(*tempNode);

						i = count;
					}


				}
			}
		}

		rows++;
	}

	//test:

	for (size_t i = 0; i < map.size(); i++)
	{
		for (size_t j = 1; j < map[1].size(); j++)////////
		{
			if(map[i][j] == true)
				std::cout << "{" << "true" << "}";
			else
				std::cout << "{" << "false" << "}";
		}
		std::cout << std::endl;
	}

	
	return 0;
}