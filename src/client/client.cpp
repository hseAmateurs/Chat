#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "ws2_32.lib")
#include <vector>
#include <winsock2.h>
#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <sstream>
#define MAXLEN 256

using namespace std;

int port;
char IP[16];

//thread thSend, thRecv;
//bool exitFlag = false;
SOCKADDR_IN addr;
SOCKET connection;

bool stableConnection = true;

void sendMessage(int clientSocket);
void handleMessage();
string dataTime();
//bool checkServer(int clientSocket);

int main(int argc, char* argv[]) {
	// ====== WSAStartup  ======
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		perror("WSAStartup error: ");
		return 1;
	}

	string name;

	cout << "Enter IP adress to connect: ";
	cin >> IP;
	cout << "Enter port: ";
	cin >> port;
	cout << "Enter your name: ";
	cin >> name;

	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr(IP);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	connection = socket(AF_INET, SOCK_STREAM, NULL);
	while (connect(connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Can't connect to the server. Enter 'try' to reconnect\n";
		string enter = "";
		cin >> enter;
		if (enter == "try")
			continue;
	}
	
	std::cout << "== Connected to the server ==\n";

	send(connection, name.c_str(), sizeof(name), 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)handleMessage, 0, 0, 0);
	string msg;
	while (1)
	{
		getline(cin, msg);
		if (msg.size() > 0)
		{
			msg = name + ": " + msg;
			send(connection, msg.c_str(), MAXLEN, 0);
		}
	}

	return 0;
}

void handleMessage()
{
	char  msg[MAXLEN];
	while (true)
	{
		int bytesReceived = recv(connection, msg, sizeof(msg), 0);
		if (bytesReceived > 0)
			cout << msg << endl;
		if (bytesReceived == -1)
		{
			string command;
			cout << "Connection lost\n";
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

/*bool checkServer(int clientSocket)
{
	
}*/