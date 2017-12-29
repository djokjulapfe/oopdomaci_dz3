#include "ListDirectory.h"
#include "FSException.h"

void ListDirectory::execute() {
	objs.clear();
	auto *dir = (Folder *) object;
	for (auto &&item : dir->getObjects()) {
		objs.push_back(item);
	}
}

void ListDirectory::print() {
	for (auto &&item : objs) {
		std::cout << item->getName() << ", ";
	}
	std::cout << std::endl;
}

ListDirectory::ListDirectory(FSObject *object) : FSOperation(object) {
	if (object->isFolder()) {
		opName = "ListDirectory";
	} else {
		throw FSException("Object is not a folder", nullptr);
	}
}
