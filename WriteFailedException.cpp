#include "WriteFailedException.h"

WriteFailedException::WriteFailedException(const std::string &msg, const FSException *cause)
		: OperationFailedException(msg, this) {
	causedBy = cause;
}
