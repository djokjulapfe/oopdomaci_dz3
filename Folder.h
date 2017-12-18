#ifndef DZ3_FOLDER_H
#define DZ3_FOLDER_H


#include <vector>
#include <algorithm>
#include "FSObject.h"
#include "FSVisitor.h"

class Folder : public FSObject {
public:
	void accept(FSVisitor &v) override;

	long size() override;

	FSObject *copy() override;

	void add(FSObject *o);

	const std::vector<FSObject *> &getObjects() const;

	void remove(FSObject *o);

private:
	std::vector<FSObject *> objects;
};


#endif //DZ3_FOLDER_H
