#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "ws2_32.lib")
#include <vector>
#include <winsock2.h>
#include <iostream>
#include <thread>
#include <string>
#include "functions.h"
#define MAXLEN 256

using namespace std;

int port;
char IP[16];

SOCKADDR_IN addr;
SOCKET connection;

bool isLoggedIn = false;

bool stableConnection = true;

void handleMessage();
//string dataTime();

int main(int argc, char* argv[]) {
	// ====== WSAStartup  ======
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		perror("WSAStartup error: ");
		return 1;
	}

	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	connection = socket(AF_INET, SOCK_STREAM, NULL);
	while (connect(connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Can't connect to the server. Enter 'try' to reconnect\n";
		string enter = "";
		cin >> enter;
		if (enter == "try")
			continue;
	}
	string msg = "";
	//std::cout << "Connected to the server. Enter any key to start\n";
	//getline(cin, msg);
	//send(connection, msg.c_str(), MAXLEN, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)handleMessage, 0, 0, 0);
	while (1)
	{
		getline(cin, msg);
		vector<string> splittedmsg = splitStringBySpace(msg);
		doCommand(splittedmsg, connection, msg);
	}

	return 0;
}

void handleMessage()
{
	string msg_buffer = "";
	char  msg[MAXLEN];
	while (true)
	{

		if (isServerOnline(connection, msg))
		{
			receiveMessageToString(msg_buffer, msg);
			if (msg_buffer.size() > 0) // if we received some chars
				cout << msg_buffer << endl;
			if (msg_buffer == "[Server] You are logged in")
				isLoggedIn = true;
		}
		else
		{
			cout << "Connection lost\n";
			return;
		}
	}
}

//  /help - выводит все команды
//  /send name_user msg - отправить личное сообщение
//  /sendroom id_room msg - отправить сообщение в папку
//  /add id_room id - пригласить в комнату (сделать проверку, находится ли он сам в комнате)
//  /leave id_room - покинуть комнату