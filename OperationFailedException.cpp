#include "OperationFailedException.h"

OperationFailedException::OperationFailedException(const std::string &msg, const FSException &cause)
		: FSException(msg, *this) {
	causedBy = &cause;
}
