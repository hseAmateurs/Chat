#include "ROOM.h"

void ROOM::addUser(int id)
{
	usersId.push_back(id);
}

int ROOM::findUser(int id)
{
	int res = -1;
	for (int i = 0; i < usersId.size(); i++)
	{
		if (usersId[i] == id)
			return i;
	}
	return res;
}

bool ROOM::inRoom(int id)
{
	for (int i = 0; i < sizeRoom(); i++)
	{
		if (usersId[i] == id)
			return true;
	}
	return false;
}


//void ROOM::sendMessage(int socket, int sender, string msg)
//{
//	for (int i = 0; i < usersId.size(); i++)
//	{
//		if (i!=sender)
//			send(s.getUser(i).getSocket(), msg.c_str(), sizeof(msg), 0);
//	}
//}
