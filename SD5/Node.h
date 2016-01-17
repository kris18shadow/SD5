#pragma once
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
	delete this->name;
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
