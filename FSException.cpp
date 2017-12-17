#include "FSException.h"

FSException::FSException(const std::string &msg, const FSException &cause) : causedBy(cause) {
}

const char *FSException::what() const {
	return exception::what();
}
