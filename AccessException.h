#ifndef DZ3_ACCESSEXCEPTION_H
#define DZ3_ACCESSEXCEPTION_H


#include "FSException.h"

class AccessException : public FSException {
public:
	AccessException(const std::string &msg, const FSException *cause);

	const char *what() const throw() override;

};


#endif //DZ3_ACCESSEXCEPTION_H
