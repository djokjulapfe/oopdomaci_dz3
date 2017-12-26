#include "CreateFolder.h"

void CreateFolder::execute() {
	parent->add(new Folder(foldername));
}

CreateFolder::CreateFolder(FSObject *object, const std::string &foldername) : FSOperation(object),
																			  foldername(foldername) {
	// TODO: check if object is File *
	parent = (Folder *) object;
}
