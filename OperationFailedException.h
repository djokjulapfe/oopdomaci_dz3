#ifndef DZ3_OPERATIONFAILEDEXCEPTION_H
#define DZ3_OPERATIONFAILEDEXCEPTION_H


#include "FSException.h"

class OperationFailedException : public FSException {
public:
	OperationFailedException(const std::string &msg, const FSException *cause);

	const char *what() const throw() override;

};


#endif //DZ3_OPERATIONFAILEDEXCEPTION_H
