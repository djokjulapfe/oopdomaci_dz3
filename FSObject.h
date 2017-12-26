#ifndef DZ3_FSOBJECT_H
#define DZ3_FSOBJECT_H

#include <string>
#include <vector>
class AccessDescriptor;
class Folder;
class FSVisitor;

class FSObject {
public:

	explicit FSObject(const std::string &name);

	FSObject();

	virtual ~FSObject();

	const std::string &getName() const;

	AccessDescriptor *getAccessDescriptor() const;

	virtual void accept(FSVisitor &v) = 0;

	virtual long size() = 0;

	virtual FSObject *copy() = 0;

public:
	Folder *parent;

	static int counter;

	AccessDescriptor *accessDescriptor;

protected:
	std::string name;
};


#endif //DZ3_FSOBJECT_H
