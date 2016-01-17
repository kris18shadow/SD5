#pragma once
#include <vector>

class Node
{
private:
	char* name;
public:
	Node() : name("noName") {};
	~Node();
	char* getName() const;
	void setName(char* newName);
};

Node::~Node()
{
	//delete this->name;
}

char* Node::getName() const
{
	return this->name;
}

void Node::setName(char* newName)
{
	name = new char[strlen(newName) + 1];
	strcpy(this->name, newName);
}

class Group;
//////////
//People//
//////////
class People : public Node
{
private:
	std::vector<People*> connections;
	std::vector<Group*> groups;
public:
	std::vector<People*> getConnections() const;
	void addConnection(People* connection);
	std::vector<Group*> getGroups() const;
	void addGroup(Group* group);
};

std::vector<People*> People::getConnections() const
{
	return this->connections;
}

void People::addConnection(People* connection)
{
	this->connections.push_back(connection);
}

std::vector<Group*> People::getGroups() const
{
	return this->groups;
}

void People::addGroup(Group* group)
{
	this->groups.push_back(group);
}

/////////
//Group//
/////////
class Group : public Node
{
private:
	std::vector<People*> members;
public:
	std::vector<People*> getMembers() const;
	void addMember(People* member);
};

std::vector<People*> Group::getMembers() const
{
	return this->members;
}

void Group::addMember(People* member)
{
	this->members.push_back(member);
}