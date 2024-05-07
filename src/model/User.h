#pragma once
#include <iostream>
#include <stdio.h>
using namespace std;

class User {
	int id;
	string login;
	string password;
	bool isOnline;
public:
	void setOnline();
	int getId() const;
};