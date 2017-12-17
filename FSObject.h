#ifndef DZ3_FSOBJECT_H
#define DZ3_FSOBJECT_H

#include <string>
#include "FSVisitor.h"
#include "AccessDescriptor.h"

class FSObject {
public:

	const std::string &getName() const;

	AccessDescriptor *getAccessDescriptor() const;

	virtual void accept(FSVisitor v) = 0;

	virtual long size() = 0;

	virtual FSObject copy() = 0;

private:

	std::string name;
	AccessDescriptor *accessDescriptor;
	Folder *parent;
};


#endif //DZ3_FSOBJECT_H
