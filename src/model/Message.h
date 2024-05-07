#pragma once
#include <iostream>
#include <stdio.h>
#include "Status.h"
#include "Folder.h"
#include <ctime>
using namespace std;

class Message {
	int id;
	int statusId;
	Status* status;
	string text;
	int folderId;
	Folder* folder;
	time_t sendTime;
public:
	Message(string t, Folder* f, Status* begin);
	void Sended(Status* end);
};