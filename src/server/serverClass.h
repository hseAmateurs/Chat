#pragma once

#pragma comment(lib, "ws2_32.lib")
#include <vector>
#include <winsock2.h>
#include <iostream>
#include "user.h"
#include "room.h"


struct Command {
	string command;
	string token1;
	string token2;
};

using namespace std;

class SERVER
{
private:
	static int usersCounter;
	static int roomsCounter;
	SOCKET serverSocket;
	SOCKADDR_IN addr;
	vector<USER> users;
	vector<ROOM> rooms;
public:
	SERVER(const char ip[], int port);
	bool tryLogin(int clientSocket, int& userId);
	void sendAll(int id_sender, const char buf[]);
	void doCommand(const Command& command, int userId);
	void pushUser(string name, string password, SOCKET socket);
	//void pushUser(USER user);
	USER getUser(int index) const { return users[index]; };
	void setSocket(int index, int socket);
	void setName(int index, string name);
	int findUser(string name);
	int findRoom(string name);
	SOCKET getSocket() const { return serverSocket; };
	SOCKADDR_IN getAddr() const { return addr; };
	static void increaseCounter() { usersCounter++; }
	static int getCounter() { return usersCounter; };
	static void increaseRoomsCounter() { roomsCounter++; }
	static int getRoomsCounter() { return roomsCounter; };
	void pushRoom(string name);
};

Command parseCommand(const string& input);


