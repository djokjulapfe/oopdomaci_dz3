#include "CreateFile.h"
#include "NameCollisionException.h"

void CreateFile::execute() {
	for (auto &&item : parent->containedObjects) {
		if (item->getName() == filename) throw NameCollisionException("There exist a file with that name", nullptr);
	}
	parent->add(new File(filename));
}

CreateFile::CreateFile(Folder *parent, const std::string &filename) : parent(parent), filename(filename) {
}
