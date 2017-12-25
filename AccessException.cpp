#include "AccessException.h"

AccessException::AccessException(const std::string &msg, const FSException *cause) : FSException(msg, cause) {
	causedBy = this;
}
