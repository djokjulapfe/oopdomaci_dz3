#include "ProtectedOperation.h"

void ProtectedOperation::execute() {
	if (checkPrecondition()) {
		wrappedOperation->execute();
	}
}

ProtectedOperation::ProtectedOperation(FSOperation *wrappedOperation) : wrappedOperation(wrappedOperation) {
}

bool ProtectedOperation::checkPrecondition() {
	for (auto &&item : wrappedOperation->objects) {
		auto acc = item->getAccessDescriptor();
		bool hasAccess = false;
		for (auto &&operation : acc->getAllowedOperations()) {
			if (operation == wrappedOperation->getName()) {
				hasAccess = true;
				break;
			}
		}
		if (!hasAccess) return false;
	}
	return true;
}
