#ifndef DZ3_DELETEOBJECT_H
#define DZ3_DELETEOBJECT_H


#include "FSOperation.h"
#include "Folder.h"

class DeleteObject : public FSOperation {

public:
	DeleteObject(FSObject *object);

	void execute() override;

};


#endif //DZ3_DELETEOBJECT_H
