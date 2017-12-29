#include "Move.h"

void Move::execute() {
	object->parent->remove(object);
	dest->add(object);
}

Move::Move(FSObject *object, Folder *dest) : FSOperation(object), dest(dest) {
	opName = "Move";
}
