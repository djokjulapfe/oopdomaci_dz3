#include "CopyPaste.h"

void CopyPaste::execute() {
	destFolder->add(object->copy());
}

CopyPaste::CopyPaste(FSObject *object, Folder *destFolder, const std::string &newName) : FSOperation(object),
																						 destFolder(destFolder),
																						 newName(newName) {
}


