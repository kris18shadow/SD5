#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "NodeDerivatives.h"

class Solver
{
private:
	std::vector< std::vector <bool> > map; //shows which person is in wich group
	std::vector<Group> groupNames;
	std::vector<People> people;
	
	void readFromFile(std::string filePath);
	unsigned findCommonMembers(Group &left, Group &right);
	void generateRelations();

public:
	Solver(std::string filePath);	
	void printMostConnectedGroups();
	void printMostConnectedPeople();
};