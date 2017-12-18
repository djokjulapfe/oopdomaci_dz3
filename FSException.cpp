#include <iostream>
#include "FSException.h"

FSException::FSException(const std::string &msg, const FSException &cause) : exception(), causedBy(&cause) {
}

const char *FSException::what() const throw() {
	return "FSException";
}

void FSException::FilesystemException(std::string msg) {
	std::cout << msg;
}
