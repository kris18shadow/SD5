#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Solver.h"

int main(int argc, char* argv[])
{
	std::string filePath = argv[1];
	std::cout << "Path entered: " << filePath << std::endl;
	
	Solver Solver(filePath);

	Solver.printMostConnectedPeople();
	Solver.printMostConnectedGroups();

	return 0;
}