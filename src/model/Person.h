#pragma once
#include <iostream>
#include <stdio.h>
#include "User.h"
using namespace std;

class Person {
	int id;
	int userId;
	User user;
	string name;
public:
	Person(string name, User u);
};