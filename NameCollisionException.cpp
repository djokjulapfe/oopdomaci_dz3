#include "NameCollisionException.h"

NameCollisionException::NameCollisionException(const std::string &msg, const FSException *cause)
		: OperationFailedException(msg, this) {
	causedBy = cause;
}
