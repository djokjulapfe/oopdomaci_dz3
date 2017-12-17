#include "Folder.h"

const std::vector<FSObject *> &Folder::getObjects() const {
	return objects;
}

void Folder::accept(FSVisitor v) {
	FSObject::accept(v);
}
