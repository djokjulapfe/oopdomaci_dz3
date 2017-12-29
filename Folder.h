#ifndef DZ3_FOLDER_H
#define DZ3_FOLDER_H


#include <vector>
#include <algorithm>
#include <iostream>
#include "FSObject.h"
#include "FSVisitor.h"
#include "AccessDescriptor.h"

class Folder : public FSObject {
public:
	explicit Folder(const std::string &name);

	Folder();

	~Folder();

	void accept(FSVisitor &v) override;

	long size() override;

	FSObject *copy() override;

	void add(FSObject *o);

	const std::vector<FSObject *> &getObjects() const;

	void remove(FSObject *o);

	bool isFolder() override;

	std::vector<FSObject *> containedObjects;
};


#endif //DZ3_FOLDER_H
