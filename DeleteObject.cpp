#include "DeleteObject.h"

void DeleteObject::execute() {
	object->parent->remove(object);
	delete object;
}

DeleteObject::DeleteObject(FSObject *object) : FSOperation(object) {
}
