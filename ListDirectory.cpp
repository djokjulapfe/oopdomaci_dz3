#include "ListDirectory.h"

void ListDirectory::execute() {
	// TODO: check if object is Folder
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
	opName = "ListDirectory";
}
