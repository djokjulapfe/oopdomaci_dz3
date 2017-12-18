#include "AccessDescriptor.h"

const std::vector<std::string> &AccessDescriptor::getAllowedOperations() const {
	return allowedOperations;
}

void AccessDescriptor::add(std::string operationName) {
	allowedOperations.push_back(operationName);
}

void AccessDescriptor::remove(std::string operationName) {
	allowedOperations.erase(std::remove(allowedOperations.begin(), allowedOperations.end(), operationName), allowedOperations.end());
}

bool AccessDescriptor::checkAccess(std::string operationName) {
	return std::find(allowedOperations.begin(), allowedOperations.end(), operationName) != allowedOperations.end();
}


