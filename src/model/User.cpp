#include "User.h"

void User::setOnline()
{
		if (isOnline) isOnline = false;
		else isOnline = true;
}

int User::getId() const
{
	return id;
}
