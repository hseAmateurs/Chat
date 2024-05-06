#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "ws2_32.lib")
#include <vector>
#include <winsock2.h>
#include <iostream>
#include <thread>
#include <string>
#define MAXLEN 256

using namespace std;

void handleClient(int clientSocket);


int main(int argc, char* argv[]) {

	// ====== WSAStartup  ======
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		perror("WSAStartup error: ");
		exit(-1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;


	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, NULL);
	bind(serverSocket, (SOCKADDR*)&addr, sizeof(addr));
	listen(serverSocket, SOMAXCONN);

	std::cout << "Server is online\n";

	SOCKADDR_IN Client;
	int clientSocket;

	while (1)
	{
		if ((clientSocket = accept(serverSocket, (struct sockaddr*)&addr, &sizeofaddr)) == -1)
		{
			perror("Accept error: ");
			exit(-1);
		}
		handleClient(clientSocket);
		//string test = "test";
		//send(clientSocket, test.c_str(), sizeof(test), 0);
		//Sleep(3000);
	}

	closesocket(serverSocket);
	return 0;
}




void handleClient(int clientSocket)
{
	//cout <<"waiting...\n";
	char buffer[256];
	memset(buffer, 0, sizeof(buffer));
	int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
	cout << buffer << " is received\n";
	string response = "Message " + string(buffer) + " is successfully received";
	send(clientSocket, response.c_str(), sizeof(response), 0);
}
