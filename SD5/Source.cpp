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

	std::vector<Group> groupNames;
	std::vector<People> people;

	while (file.good())
	{		
		std::getline(file, value, '\n');
		

		//Reading Group names at the first row:
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

					Group* tempNode = new Group;
					tempNode->setName(temp);
					groupNames.push_back(*tempNode);

					i = count;
				}
			}
		}
		else
		{
			map.resize(rows );
			for (size_t i = 0; i < value.length(); i++)
			{
				if (value[i] != ',' && value[i] != ';')
				{
					if (isdigit(value[i]))
					{
						if (value[i] == '0')
							map[rows - 1].push_back(false);
						else
							map[rows - 1].push_back(true);

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

						People* tempNode = new People;
						tempNode->setName(temp);
						people.push_back(*tempNode);

						i = count;
					}
				}
			}
		}

		rows++;
	}

	for (size_t i = 0; i < map.size(); i++)
	{
		for (size_t j = 0; j < map[0].size(); j++)
		{
			if (map[i][j] == true)
			{
				groupNames[j].addMember(&people[i]);
				people[i].addGroup(&groupNames[i]);
			}
		}
	}



	//test:

	for (size_t i = 0; i < map.size(); i++)
	{
		for (size_t j = 0; j < map[0].size(); j++)
		{
			if(map[i][j] == true)
				std::cout << "{" << "true" << "}";
			else
				std::cout << "{" << "false" << "}";
		}
		std::cout << std::endl;
	}

	for (size_t i = 0; i < people.size(); i++)
	{
		std::cout << people[i].getName() << std::endl;
	}
	std::cout << "\n@@@@@@@@@@@@@@@@@@@\n";
	for (size_t i = 0; i < groupNames.size(); i++)
	{
		std::cout << groupNames[i].getName() << std::endl;
	}
	
	return 0;
}