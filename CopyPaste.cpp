#include "CopyPaste.h"

void CopyPaste::execute() {
	auto tmp = object->copy();
	tmp->setName(newName);
	destFolder->add(tmp);
}

CopyPaste::CopyPaste(FSObject *object, Folder *destFolder, const std::string &newName) : FSOperation(object),
																						 destFolder(destFolder),
																						 newName(newName) {
	opName = "CreateFile";
}


