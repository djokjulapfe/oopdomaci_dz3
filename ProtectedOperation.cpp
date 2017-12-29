#include "ProtectedOperation.h"
#include "FSException.h"
#include "AccessException.h"

void ProtectedOperation::execute() {
	if (checkPrecondition()) {
		wrappedOperation->execute();
	} else {
		throw AccessException(wrappedOperation->opName, nullptr);
	}
}

ProtectedOperation::ProtectedOperation(FSOperation *fsOperation) {
	wrappedOperation = fsOperation;
	opName = "ProtectedOperation";
}

bool ProtectedOperation::checkPrecondition() {
	return wrappedOperation->object->getAccessDescriptor()->checkAccess(wrappedOperation->opName);
}
