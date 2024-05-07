#include "Message.h"

Message::Message(string t, Folder* f, Status* begin)
{
	text = t;
	folder = f;
	folderId = f->getId();
	status = begin;
}

void Message::Sended(Status* end)
{
	status = end;
	sendTime = time(0);
}