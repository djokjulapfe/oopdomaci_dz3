#ifndef DZ3_LISTDIRECTORY_H
#define DZ3_LISTDIRECTORY_H


#include "FSOperation.h"
#include "Folder.h"

class ListDirectory : public FSOperation {
public:
	ListDirectory(FSObject *object);

	void execute() override;

	void print();

	std::vector<FSObject *> objs;

};


#endif //DZ3_LISTDIRECTORY_H
