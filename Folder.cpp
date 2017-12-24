#include "Folder.h"

const std::vector<FSObject *> &Folder::getObjects() const {
	return containedObjects;
}

void Folder::accept(FSVisitor &v) {
	v.visitFolder(*this);
}

long Folder::size() {
	long ret = 0;
	for (auto &&item : containedObjects) {
		ret += item->size();
	}
	return ret;
}

FSObject *Folder::copy() {
	// TODO: implement
	return nullptr;
}

void Folder::add(FSObject *o) {
	containedObjects.push_back(o);
}

void Folder::remove(FSObject *o) {
	containedObjects.erase(std::remove(containedObjects.begin(), containedObjects.end(), o), containedObjects.end());
}

Folder::Folder(const std::string &name) : FSObject(name) {

}

Folder::Folder() : FSObject() {
}

Folder::~Folder() {
	for (auto item : containedObjects) {
		delete item;
	}
}
