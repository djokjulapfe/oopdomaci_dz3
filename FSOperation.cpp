#include "FSOperation.h"

const std::string &FSOperation::getName() const {
	return opName;
}

FSOperation::FSOperation(FSObject *object) : object(object) {
}

FSOperation::FSOperation() = default;
