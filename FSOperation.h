#ifndef DZ3_FSOPERATION_H
#define DZ3_FSOPERATION_H


#include <vector>
#include "FSObject.h"

class FSOperation {
public:
	std::vector<FSObject *> objects;

	virtual void execute() = 0;

	const std::string &getName() const;
private:
	std::string opName;
};


#endif //DZ3_FSOPERATION_H
