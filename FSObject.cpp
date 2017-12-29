#include "FSObject.h"
#include "AccessDescriptor.h"

int FSObject::counter = 0;

const std::string &FSObject::getName() const {
	return name;
}

AccessDescriptor *FSObject::getAccessDescriptor() const {
	return accessDescriptor;
}

FSObject::FSObject(const std::string &name) : name(name) {
	accessDescriptor = new AccessDescriptor();
	parent = nullptr;
}

FSObject::FSObject() {
	accessDescriptor = new AccessDescriptor();
	name = "unnamedObject_";
	name.append(std::to_string(FSObject::counter));
	FSObject::counter++;
	parent = nullptr;
}

FSObject::~FSObject() {
	delete accessDescriptor;
}

void FSObject::setName(const std::string &name) {
	FSObject::name = name;
}
