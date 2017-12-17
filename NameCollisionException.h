#ifndef DZ3_NAMECOLLISIONEXCEPTION_H
#define DZ3_NAMECOLLISIONEXCEPTION_H


#include "OperationFailedException.h"

class NameCollisionException : public OperationFailedException {
public:
	NameCollisionException(const std::string &msg, const FSException &cause);

};


#endif //DZ3_NAMECOLLISIONEXCEPTION_H
