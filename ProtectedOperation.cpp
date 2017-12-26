#include "ProtectedOperation.h"
#include "FSException.h"
#include "AccessException.h"

void ProtectedOperation::execute() {
	if (checkPrecondition()) {
		wrappedOperation->execute();
	} else {
		throw AccessException(opName, nullptr);
	}
}

ProtectedOperation::ProtectedOperation(FSOperation *wrappedOperation) : wrappedOperation(wrappedOperation) {
}

bool ProtectedOperation::checkPrecondition() {
	return wrappedOperation->object->getAccessDescriptor()->checkAccess(opName);
}
