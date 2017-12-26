#include "AccessException.h"

AccessException::AccessException(const std::string &msg, const FSException *cause) : FSException(msg, cause) {
	causedBy = this;
}

const char *AccessException::what() const throw() {
	return "AccessException\n";
}
