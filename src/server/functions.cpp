#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include "functions.h"
#include <sstream>
#include <chrono>
#include "serverClass.h"

string dataTime() // return time in [yyyy-mm-dd hh:mm:ss] format
{
	auto now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);

	struct tm* parts = std::localtime(&now_c);

	std::stringstream ss;
	ss << "[" << (parts->tm_year + 1900) << "-" << (parts->tm_mon + 1) << "-" << parts->tm_mday << " ";
	ss << parts->tm_hour << ":" << parts->tm_min << ":" << parts->tm_sec << "]";

	return ss.str();
}

pair<string, string> splitString(const string& input)
{
	size_t pos = input.find(' ');
	if (pos == string::npos) {
		return make_pair(input, "");
	}
	else {
		return make_pair(input.substr(0, pos), input.substr(pos + 1));
	}
}

void onlineNotifier(const SERVER& server, int userId)
{
	string msg = "User " + server.getUser(userId).getName() + " is online!";
	cout << dataTime() + " " + msg << endl;
	msg = "[Server] " + msg;

	for (int i = 0; i < SERVER::getCounter(); i++)
	{
		if (i != userId)
			send(server.getUser(i).getSocket(), msg.c_str(), sizeof(msg), 0); // notify user is online
	}

	msg = "[Server] You are online! Your id is " + to_string(userId);
	send(server.getUser(userId).getSocket(), msg.c_str(), sizeof(msg), 0);
}
