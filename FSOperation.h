#ifndef DZ3_FSOPERATION_H
#define DZ3_FSOPERATION_H


#include <vector>
#include "FSObject.h"

class FSOperation {
public:
	virtual void execute();

	const std::string &getOpName() const;

private:
	std::vector<FSObject *> objects;
	std::string opName;
};


#endif //DZ3_FSOPERATION_H
