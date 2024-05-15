#pragma once
#include <iostream>
#include <WinSock2.h>
#include <vector>

using namespace std;

void receiveMessageToString(string &destination, const char sourse[]);
bool isServerOnline(SOCKET connection, char msg[]);
vector<string> splitStringBySpace(const string& str);
void doCommand(vector<string> splittedmsg, const SOCKET connection, const string& recvmsg);
