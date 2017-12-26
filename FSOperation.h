#ifndef DZ3_FSOPERATION_H
#define DZ3_FSOPERATION_H


#include <vector>
#include "FSObject.h"

class FSOperation {
public:
	FSObject * object;

	virtual void execute() = 0;

	const std::string &getName() const;

protected:
	std::string opName;
};


#endif //DZ3_FSOPERATION_H
