#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "ws2_32.lib")
#include <vector>
#include <winsock2.h>
#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <chrono>
#include "serverClass.h"
#include "functions.h"

mutex mtx;

#define MAXLEN 4096

#define MAXCONNECTIONS 100000

//int port;
//char IP[16];

using namespace std;

void handleClient(SOCKET clientSocket);

SERVER server("127.0.0.1", 1111); // in fact, it does not depend on the entered data (check constructor)
SOCKET clientSocket;

int main(int argc, char* argv[]) {
	SOCKADDR_IN Client;
	SOCKET clientSocket;
	int sizeofaddr = sizeof(server.getAddr());
	char buffer[MAXLEN] = { 0 };
	SOCKADDR_IN serverAddr = server.getAddr();

	for (int i = 0; i < MAXCONNECTIONS; i++)
	{
		if ((clientSocket = accept(server.getSocket(), (SOCKADDR*)&serverAddr, &sizeofaddr)))
		{
			//if (recv(clientSocket, buffer, MAXLEN, 0) != -1)
			//{	
			//	{
			//		////cout << buffer << endl;
			//		//while ((string)buffer != "CONNECT")
			//		//{
			//		//	recv(clientSocket, buffer, MAXLEN, 0);
			//		//}
					CreateThread(0, 0, (LPTHREAD_START_ROUTINE)handleClient, (LPVOID)(clientSocket), 0, 0);
			//	}
			//}
		}
	}

	system("pause");
	return 0;
}




void handleClient(SOCKET clientSocket)
{
	int userId = -1;

	char buf[MAXLEN];
	pair<string, string> splitted;
	string msg = "";
	msg = "[Server] Please enter login and password";
	send(clientSocket, msg.c_str(), sizeof(msg)+1, 0);
	bool loggedIn = false;
	while (!server.tryLogin(clientSocket, userId)) // try to log in
	{
		continue;
	}

	// client online! 


	if (userId != -1)
	{
		onlineNotifier(server, userId); // notify all 
	}
	while (1)
	{
		memset(buf, 0, MAXLEN);
		int bytesReceived = recv(clientSocket, buf, MAXLEN, 0);
		if (bytesReceived > 0)
		{
			cout << dataTime() << " << " << buf << " >> is received by server from " << server.getUser(userId).getName() << endl;
			if (buf[0] != '/')
				server.sendAll(userId, buf); // send all
			else
			{
				msg = buf;
				Command cmd = parseCommand(msg);
				server.doCommand(cmd, userId);
			}

		}
		if (bytesReceived == -1)
		{
			if (userId != -1)
			{
				msg = "[Server] User #" + to_string(userId) + " " + server.getUser(userId).getName() + " is offline";
				for (int i = 0; i < SERVER::getCounter(); i++)
					if (i != userId)
						send(server.getUser(i).getSocket(), msg.c_str(), sizeof(msg), 0);
				server.setSocket(userId, -1);
			}
			closesocket(clientSocket); // close connection
			msg = dataTime() + " " + msg;
			cout << msg << endl;
			return;
		}
	}
}
