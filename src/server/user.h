#pragma once
#include <vector>
#include <winsock2.h>
#include <iostream>

using namespace std;

class USER
{
private:
	int id;
	string name;
	string password;
	int userSocket;
public:
	USER() : id(-1), name(""), password(""), userSocket(-1) {};
	USER(int id, string login, string password, SOCKET socket) :
		id(id), name(login), password(password), userSocket(socket) {};
	void changeName(string newname) {
		name = newname;
	};
	bool isOnline() {
		return (userSocket != INVALID_SOCKET);
	}
	string getName() { return name; };
	string getPas() { return password; };
	SOCKET getSocket() { return userSocket; };
	void setSocket(int socket) { userSocket = socket; }
};