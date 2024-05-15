#include "functions.h"
#include <sstream>

void receiveMessageToString(string &destination, const char sourse[])
{
	destination = "";
	int i = 0;
	while (sourse[i] != '\0')
	{
		destination = destination + sourse[i++];
	}
}

bool isServerOnline(SOCKET connection, char msg[])
{
	int bytesReceived = recv(connection, msg, 256, 0);
	if (bytesReceived == -1)
		return false;
	return true;
}

vector<string> splitStringBySpace(const string& str)
{
	vector<string> result;
	istringstream iss(str);
	string token;

	while (getline(iss, token, ' ')) {
		result.push_back(token);
	}

	return result;
}

void doCommand(vector<string> splittedmsg, const SOCKET connection, const string& recvmsg)
{
	string msg = "";
	if (splittedmsg.size() > 0)
	{
		if (splittedmsg[0][0] == '/')
		{
			if (splittedmsg[0] == "/help")
			{
				cout << endl;
				cout << "========================== Commands ==========================\n";
				cout << "==          /help - displays the available commands         ==\n";
				cout << "==        /send name_user msg - send msg to the user        ==\n";
				cout << "==           /createroom name - create a new room           ==\n";
				cout << "==      /sendroom name_room msg - send msg to the room      ==\n";
				cout << "==       /add name_room name - add the user to the room     ==\n";
				cout << "==            /leave name_room - leave the room             ==    has not been implemented yet \n";
				cout << "==============================================================\n";
				cout << endl;
			}
			else if (splittedmsg[0] == "/send" && splittedmsg.size() >= 3)
			{
				msg = splittedmsg[0] + " " + splittedmsg[1] + " ";
				for (int i = 2; i < splittedmsg.size(); i++)
				{
					msg = msg + splittedmsg[i] + " ";
				} //format :   /send id msg   
				send(connection, msg.c_str(), sizeof(msg), 0);
			}
			else if (splittedmsg[0] == "/sendroom" && splittedmsg.size() >= 3)
			{
				msg = splittedmsg[0] + " " + splittedmsg[1] + " ";
				for (int i = 2; i < splittedmsg.size(); i++)
				{
					msg = msg + splittedmsg[i] + " ";
				} //format :   /sendroom name_room msg   
				send(connection, msg.c_str(), sizeof(msg), 0);
			}
			else if (splittedmsg[0] == "/add" && splittedmsg.size() == 3)
			{
				msg = splittedmsg[0] + " " + splittedmsg[1] + " " + splittedmsg[2];
				//format : /add name_droom nameuser
				send(connection, msg.c_str(), sizeof(msg), 0);
			}
			else if (splittedmsg[0] == "/leave" && splittedmsg.size() == 2)
			{
				msg = splittedmsg[0] + " " + splittedmsg[1];
				//format : /leave name_room
				send(connection, msg.c_str(), sizeof(msg), 0);
			}
			else if (splittedmsg[0] == "/createroom" && splittedmsg.size() == 2)
			{
				msg = splittedmsg[0] + " " + splittedmsg[1];
				//format : /createroom name
				send(connection, msg.c_str(), sizeof(msg), 0);
			}
			else
				cout << "Unknown command.\n";
		}
		else // it is not command
		{
			send(connection, recvmsg.c_str(), sizeof(recvmsg), 0);
		}
	}
}


//  /help - выводит все команды
//  /send id_user msg - отправить личное сообщение
//  /sendroom id_room msg - отправить сообщение в папку
//  /add id_room id - пригласить в комнату
//  /leave id_room - покинуть комнату