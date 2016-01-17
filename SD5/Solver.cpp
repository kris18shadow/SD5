#include "Solver.h"

Solver::Solver(std::string filePath)
{
	readFromFile(filePath);
	generateRelations();
}

unsigned Solver::findCommonMembers(Group &left, Group &right)
{
	unsigned counter = 0;

	for (size_t i = 0; i < left.getMembers().size(); i++)
	{
		for (size_t j = i + 1; j < right.getMembers().size(); j++)
		{
			if (left.getMembers()[i] == right.getMembers()[j])
				counter++;
		}
	}

	return counter;
}

void Solver::generateRelations()
{
	for (size_t i = 0; i < map.size(); i++)
	{
		for (size_t j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] == true)
			{
				//Add members to groups:
				groupNames[j].addMember(&people[i]);
				//Add groups to members:
				people[i].addGroup(&groupNames[j]);
			}
		}
	}

	//Look for connections between people:
	for (size_t i = 0; i < people.size(); i++)
	{
		for (size_t j = 0; j < people[i].getGroups().size(); j++)
		{
			for (size_t k = 0; k < people[i].getGroups()[j]->getMembers().size(); k++)
			{
				if (people[i].getName() != people[i].getGroups()[j]->getMembers()[k]->getName())
				{
					people[i].addConnection(people[i].getGroups()[j]->getMembers()[k]);
				}
			}
		}
	}
}

void Solver::readFromFile(std::string filePath)
{
	std::ifstream file;
	file.open(filePath);

	std::string value;
	size_t rows = 0;

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
			map.resize(rows);
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

	file.close();
}

void Solver::printMostConnectedGroups()
{
	int id1, id2;
	id1 = id2 = 0;
	int count = 0;

	for (size_t i = 0; i < groupNames.size(); i++)
	{
		for (size_t k = i; k < groupNames.size(); k++)
		{
			if (findCommonMembers(groupNames[i], groupNames[k]) > count)
			{
				id1 = i; id2 = k;
				count = findCommonMembers(groupNames[i], groupNames[k]);
			}
		}
	}

	std::cout << "Most connected groups:\n";
	std::cout << groupNames[id1].getName() << " with "
		<< groupNames[id2].getName() << std::endl;
}

void Solver::printMostConnectedPeople()
{
	//find the person with most connections:
	People* max = &people[0];

	for (size_t i = 1; i < people.size(); i++)
	{
		if (people[i].getConnections().size() > max->getConnections().size())
		{
			max = &people[i];
		}
	}

	//check for other people with same connections count:
	std::vector<People*> famousPeople;
	famousPeople.push_back(max);

	for (size_t i = 0; i < people.size(); i++)
	{
		if (people[i].getConnections().size() == max->getConnections().size() && max != &people[i])
		{
			famousPeople.push_back(&people[i]);
		}
	}

	//Print people with most connections:
	std::cout << "Most connections:\n";
	for (size_t i = 0; i < famousPeople.size(); i++)
	{
		std::cout << famousPeople[i]->getName() << std::endl;
	}
}