#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "ws2_32.lib")
#include <vector>
#include <winsock2.h>
#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#define MAXLEN 256

using namespace std;

thread thSend, thRecv;
bool exitFlag = false;
SOCKADDR_IN addr;

void sendMessage(int clientSocket);
void recvMessage(int clientSocket);
bool checkServer(int clientSocket);

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

	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(clientSocket, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Can't connect to the server\n";
		return 1;
	}
	
	std::cout << "== Connected to the server ==\n";
	/*thread receiveThread(recvMessage, clientSocket);
	thread sendingThread(sendMessage, clientSocket);*/
	//while (1)
	//{
	//	//sendMessage(clientSocket);
	//	//cout << "sending mes \n";
	//}

	////receiveThread.join();
	////sendingThread.join();

	return 0;
}

void sendMessage(int clientSocket)
{
	while (1)
	{
		string message;
		getline(cin, message);
		send(clientSocket, message.c_str(), sizeof(message), 0);
		//cout << "sending mes \n";
	}
}

void recvMessage(int clientSocket)
{
	char buffer[256];
	int bytesReceived = 0;
	while (1)
	{
		//cout << "trying to receive\n";
		bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
		if (bytesReceived > 0)
		{
			buffer[bytesReceived] = '\0';
			cout << "Message received: " << buffer << endl;
		}
	}
}

/*bool checkServer(int clientSocket)
{
	
}*/
