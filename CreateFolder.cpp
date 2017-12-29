#include "CreateFolder.h"
#include "FSException.h"

void CreateFolder::execute() {
	parent->add(new Folder(foldername));
}

CreateFolder::CreateFolder(FSObject *object, const std::string &foldername) : FSOperation(object),
																			  foldername(foldername) {
	if (object->isFolder()) {
		parent = (Folder *) object;
		opName = "CreateFolder";
	} else {
		throw FSException("Object is not a folder", nullptr);
	}
}
