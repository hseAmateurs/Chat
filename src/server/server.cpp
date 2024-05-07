#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "ws2_32.lib")
#include <vector>
#include <winsock2.h>
#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <sstream>
#define MAXLEN 256

#define MAXCONNECTIONS 10

int port;
char IP[16];

struct USER
{
	char name[256];
	SOCKET clientConnection;
}clientsOnline[MAXCONNECTIONS];
int Counter = 0;

using namespace std;

void handleClient(int clientSocket);
string dataTime();


int main(int argc, char* argv[]) {

	// ====== WSAStartup  ======
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		perror("WSAStartup error: ");
		exit(-1);
	}

	cout << "Enter IP adress for server: ";
	cin >> IP;
	cout << "Enter port: ";
	cin >> port;

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr(IP);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;


	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, NULL);
	bind(serverSocket, (SOCKADDR*)&addr, sizeof(addr));
	listen(serverSocket, SOMAXCONN);

	std::cout << "Server is online and ready to listen\n";

	SOCKADDR_IN Client;
	SOCKET clientSocket;

	for (int i = 0; i < MAXCONNECTIONS; i++)
	{
		if ((clientSocket = accept(serverSocket, (SOCKADDR*)&addr, &sizeofaddr)))
		{
			if (recv(clientSocket, clientsOnline[Counter].name, sizeof(clientsOnline[Counter].name), 0))
			{
				cout << "New user #" << Counter << ", name: " << clientsOnline[Counter].name << " connected successufully" << endl;
				Counter++;
				clientsOnline[i].clientConnection = clientSocket;
				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)handleClient, (LPVOID)(i), 0, 0);
			}
		}
	}

	system("pause");
	return 0;
}




void handleClient(int userno)
{
	//cout << "waiting...\n";
	string buffer;
	buffer = "User #" + to_string(userno) + " " + clientsOnline[userno].name + " is online";
	//cout << "online notifier len " << buffer.size();
	for (int i = 0; i < Counter; i++)
	{
		if (i != userno)
			send(clientsOnline[i].clientConnection, buffer.c_str(), MAXLEN, 0);
	}
	char msg[MAXLEN];
	while (1)
	{
		int bytesReceived = recv(clientsOnline[userno].clientConnection, msg, MAXLEN, 0);
		if (bytesReceived > 0)
		{
			cout << dataTime() <<" << " << msg << " >> is received by server from " << clientsOnline[userno].name << endl;
			//string response = "message " + string(buffer) + " is successfully received";
			buffer = msg;
			for (int i = 0; i < Counter; i++)
				if (i != userno)
					send(clientsOnline[i].clientConnection, msg, MAXLEN, 0);
		}
		if (bytesReceived == -1)
		{
			buffer = "User #" + to_string(userno) + " " + clientsOnline[userno].name + " is offline";
			for (int i = 0; i < Counter; i++)
				if (i != userno)
					send(clientsOnline[i].clientConnection, buffer.c_str(), MAXLEN, 0);
			closesocket(clientsOnline[userno].clientConnection);
			cout << "=== " << clientsOnline[userno].name << " has lost connection ===\n";
			return;
		}
	}
}

string dataTime() {
	auto now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);

	struct tm* parts = std::localtime(&now_c);

	std::stringstream ss;
	ss << "[" << (parts->tm_year + 1900) << "-" << (parts->tm_mon + 1) << "-" << parts->tm_mday << " ";
	ss << parts->tm_hour << ":" << parts->tm_min << ":" << parts->tm_sec << "]";

	return ss.str();
}
