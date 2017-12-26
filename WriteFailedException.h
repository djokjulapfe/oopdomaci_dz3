#ifndef DZ3_WRITEFAILEDEXCEPTION_H
#define DZ3_WRITEFAILEDEXCEPTION_H


#include "OperationFailedException.h"

class WriteFailedException : public OperationFailedException {
public:
	WriteFailedException(const std::string &msg, const FSException *cause);

	const char *what() const throw() override;

};


#endif //DZ3_WRITEFAILEDEXCEPTION_H
