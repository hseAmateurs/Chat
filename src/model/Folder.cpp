#include "Folder.h"

Folder::Folder(string n, Folder* p)
{
	name = n;
	parent = p;
	size = 0;
	parentId = p->getId();
}

int Folder::getId() const
{
	return id;
}

Folder* Folder::getParent() const
{
	return parent;
}
