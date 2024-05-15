#pragma once
#include <iostream>
#include <vector>

using namespace std;

class ROOM
{
private:
	string name;
	vector<int> usersId;
public:
	ROOM(string name) : name(name) {};
	string getName() { return name; };
	void addUser(int id);
	int findUser(int id);
	int getUserFromVector(int index) { return usersId[index]; }
	int sizeRoom() { return usersId.size(); }
	bool inRoom(int id);
};
