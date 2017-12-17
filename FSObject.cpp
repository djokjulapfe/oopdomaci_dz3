#include "FSObject.h"

const std::string &FSObject::getName() const {
	return name;
}

AccessDescriptor *FSObject::getAccessDescriptor() const {
	return accessDescriptor;
}
