#include "WriteFailedException.h"

WriteFailedException::WriteFailedException(const std::string &msg, const FSException *cause)
		: OperationFailedException(msg, this) {
	causedBy = cause;
}

const char *WriteFailedException::what() const throw() {
	return "WriteFailedException\n";
}
