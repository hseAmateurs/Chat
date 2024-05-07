#pragma once
#include <iostream>
#include <stdio.h>
using namespace std;

class Folder {
	int id;
	int parentId;
	Folder* parent;
	string name;
	int size;
public:
	Folder(string n, Folder* p);
	int getId() const;
	Folder* getParent() const;
};