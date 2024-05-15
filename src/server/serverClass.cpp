#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define MAXLEN 256

#include "serverClass.h"
#include "functions.h"
#include <sstream>
#include <iostream>

using namespace std;

int SERVER::usersCounter = 0;
int SERVER::roomsCounter = 0;

SERVER::SERVER(const char ip[], int port) // in fact, it does not depend on the entered data
{
	//wsaStartup

	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
		throw ("WSAStartup error");

	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	serverSocket = socket(AF_INET, SOCK_STREAM, NULL);
	if (serverSocket == INVALID_SOCKET)
		cout << "Creating serverSocket error\n";

	int bindInfo = bind(serverSocket, (SOCKADDR*)&addr, sizeof(addr));
	if (bindInfo == -1)
		cout << "Binding error\n";

	int listenInfo = listen(serverSocket, SOMAXCONN);
	if (listenInfo == -1)
		cout << "Listeting error\n";

	cout << dataTime() << " Server is online and ready to listen\n"; // cout time and message
}

bool SERVER::tryLogin(int clientSocket, int& userId)
{
	char buf[MAXLEN];
	string msg;
	pair<string, string> splitted;
	//msg = "Please enter login and password\n"; // format: XXXXXX XXXXX - separated by " "
	memset(buf, 0, MAXLEN);
	if (recv(clientSocket, buf, MAXLEN, 0) == -1)
		return false;
	splitted = splitString((string)buf);
	if (splitted.first == "" || splitted.second == "")
	{
		msg = "[Server] Login or password can't be empty";
		send(clientSocket, msg.c_str(), sizeof(msg)+1, 0);
		return false;
	}
	int indexUser = findUser(splitted.first);
	if (indexUser != -1) // we already have this user in database
	{
		if (getUser(indexUser).getPas() == splitted.second) // compare passwords
		{
			if (getUser(indexUser).isOnline())
			{
				msg = "[Server] This account is already online!";
				send(clientSocket, msg.c_str(), sizeof(msg), 0);
				return false;
			}
			else
			{
				userId = indexUser;
				setSocket(userId, clientSocket);
				msg = "[Server] You are logged in";
				send(clientSocket, msg.c_str(), sizeof(msg), 0);
				return true;
			}
		}
		else
		{
			msg = "[Server] Wrong password. Try again!";
			send(clientSocket, msg.c_str(), sizeof(msg), 0);
			return false;
		}
	}
	else
	{
		pushUser(splitted.first, splitted.second, clientSocket); // register
		userId = SERVER::getCounter() - 1;
		msg = "[Server] Registration is successful!";
		send(clientSocket, msg.c_str(), sizeof(msg), 0);
		msg = "[Server] You are logged in";
		send(clientSocket, msg.c_str(), sizeof(msg), 0);
		return true;
	}
}

void SERVER::sendAll(int id_sender, const char buf[])
{
	string msg = "[" + getUser(id_sender).getName() + "] " + buf;
	for (int i = 0; i < SERVER::getCounter(); i++)
		if (i != id_sender)
			send(getUser(i).getSocket(), msg.c_str(), sizeof(msg), 0);
}

void SERVER::doCommand(const Command& command, int userId)
{
	if (command.command == "/send")
	{
		string receiver = command.token1;
		int indexReceiver = findUser(receiver);
		if (indexReceiver >= 0)
		{
			string msg = "[" + getUser(userId).getName() + "->YOU] " + command.token2;
			send(users[findUser(receiver)].getSocket(), msg.c_str(), sizeof(msg) + 1, 0);
			return;
		}
		else
		{
			string msg = "[Server] Can't find user " + command.token1;
			send(getUser(userId).getSocket(), msg.c_str(), sizeof(msg) + 1, 0);
			return;
		}
	}
	else if (command.command == "/createroom")
	{
		for (int i = 0; i < SERVER::getRoomsCounter(); i++)
		{
			if (rooms[i].getName() == command.token1)
			{
				string msg = "[Server] Room " + command.token1 + " is already exist";
				send(getUser(userId).getSocket(), msg.c_str(), sizeof(msg) + 1, 0);
				return;
			}
		}
		
		pushRoom(command.token1);
		rooms[SERVER::getRoomsCounter() - 1].addUser(userId);
		string msg = "[Server] Room " + command.token1 + " has been created";
		send(getUser(userId).getSocket(), msg.c_str(), sizeof(msg) + 1, 0);
		return;
	}
	else if (command.command == "/add")
	{
		int roomId = findRoom(command.token1);
		int userAdd = findUser(command.token2);

		if (roomId < 0)
		{
			string msg = "[Server] Can't find room " + command.token1;
			send(getUser(userId).getSocket(), msg.c_str(), sizeof(msg) + 1, 0);
			return;
		}
		if (userAdd < 0)
		{
			string msg = "[Server] Can't find user " + command.token2;
			send(getUser(userId).getSocket(), msg.c_str(), sizeof(msg) + 1, 0);
			return;
		}


		if (!rooms[roomId].inRoom(userId))
		{
			string msg = "[Server] You should be in room " + command.token1 + " to add someone";
			send(getUser(userId).getSocket(), msg.c_str(), MAXLEN, 0);
			return;
		}
		if (rooms[roomId].inRoom(userAdd))
		{
			string msg = "[Server] " + command.token2 + " is alredy in room " + command.token1;
			send(getUser(userId).getSocket(), msg.c_str(), sizeof(msg) + 1, 0);
			return;
		}
		if (roomId >= 0 && userAdd >= 0)
		{
			rooms[roomId].addUser(userAdd);
			string msg = "[Server] User " + getUser(userId).getName() + " added you to the room " + command.token1;
			send(getUser(userAdd).getSocket(), msg.c_str(), MAXLEN, 0);
			msg = "[Server] User " + command.token2 + " is in room " + command.token1 + " now";
			for (int i = 0; i < SERVER::getCounter(); i++)
			{
				if (i != userAdd && rooms[roomId].inRoom(i))
					send(getUser(i).getSocket(), msg.c_str(), sizeof(msg) + 1, 0);
			}
			return;
		}
	}
	else if (command.command == "/sendroom")
	{
		int roomId = findRoom(command.token1);
		if (roomId >= 0)
		{
			for (int i = 0; i < rooms[roomId].sizeRoom(); i++)
			{
				int id = rooms[roomId].getUserFromVector(i);
				if (id != userId)
				{
					string msg = "[" + getUser(userId).getName() + ":" + rooms[roomId].getName() + "] " + command.token2;
					send(getUser(id).getSocket(), msg.c_str(), sizeof(msg) + 1, 0);
				}
			}
		}
		else
		{
			string msg = "[Server] Can't find room " + command.token1;
			send(getUser(userId).getSocket(), msg.c_str(), sizeof(msg) + 1, 0);
			return;
		}
		return;
	}
	{
		string msg = "Command not found";
		send(getUser(userId).getSocket(), msg.c_str(), sizeof(msg) + 1, 0);
		return;
	}
		string msg = "Unknown error";
		send(getUser(userId).getSocket(), msg.c_str(), sizeof(msg) + 1, 0);
		return;
}

void SERVER::pushUser(string name, string password, SOCKET socket)
{
	USER newUser(SERVER::getCounter(), name, password, socket);
	users.push_back(newUser);
	SERVER::increaseCounter();
}


void SERVER::setSocket(int index, int socket)
{
	for (int i = 0; i < SERVER::getCounter(); i++)
	{
		if (i == index)
			users[i].setSocket(socket);
	}
}

void SERVER::setName(int index, string name)
{
	for (int i = 0; i < SERVER::getCounter(); i++)
	{
		if (i == index)
			users[i].changeName(name);
	}
}

int SERVER::findUser(string name)
{
	int result = -1;
	for (int i = 0; i < SERVER::getCounter(); i++)
	{
		if (users[i].getName() == name)
		{
			result = i;
			break;
		}
	}
	return result; // -1 - not found
}

int SERVER::findRoom(string name)
{
	int result = -1;
	for (int i = 0; i < SERVER::getRoomsCounter(); i++)
	{
		if (rooms[i].getName() == name)
		{
			result = i;
			break;
		}
	}
	return result; // -1 - not found
}

void SERVER::pushRoom(string name)
{
	ROOM newroom(name);
	rooms.push_back(newroom);
	SERVER::increaseRoomsCounter();
}

Command parseCommand(const string& input)
{
		istringstream iss(input);
		vector<std::string> tokens;
		string token;

		while (iss >> token) {
			tokens.push_back(token);
		}

		Command cmd;

		if (tokens.size() >= 2) {
			cmd.command = tokens[0];
			cmd.token1 = tokens[1];

			if (tokens.size() >= 3) {
				std::ostringstream oss;
				for (size_t i = 2; i < tokens.size(); ++i) {
					if (i > 2) {
						oss << " ";
					}
					oss << tokens[i];
				}
				cmd.token2 = oss.str();
			}
		}

		return cmd;
}
