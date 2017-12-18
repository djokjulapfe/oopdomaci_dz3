#include "Folder.h"

const std::vector<FSObject *> &Folder::getObjects() const {
	return objects;
}

void Folder::accept(FSVisitor &v) {
	v.visitFolder(*this);
}

long Folder::size() {
	long ret = 0;
	for (auto &&item : objects) {
		ret += item->size();
	}
	return ret;
}

FSObject *Folder::copy() {
	// TODO: implement
	return nullptr;
}

void Folder::add(FSObject *o) {
	objects.push_back(o);
}

void Folder::remove(FSObject *o) {
	objects.erase(std::remove(objects.begin(), objects.end(), o), objects.end());
}


