#include "CreateFile.h"
#include "NameCollisionException.h"

void CreateFile::execute() {
	for (auto &&item : ((Folder *) object)->containedObjects) {
		if (item->getName() == filename) throw NameCollisionException("There exist a file with that name", nullptr);
	}
	((Folder *) object)->add(new File(filename));
}

CreateFile::CreateFile(FSObject *object, const std::string &filename) : FSOperation(object), filename(filename) {
	opName = "CreateFile";
}
