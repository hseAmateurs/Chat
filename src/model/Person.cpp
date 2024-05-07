#include "Person.h"

Person::Person(string n, User u)
{
	name = n;
	user = u;
	userId = u.getId();
}
