#ifndef DZ3_MOVE_H
#define DZ3_MOVE_H


#include "FSOperation.h"
#include "Folder.h"

class Move : public FSOperation {
public:
	void execute() override;

	Move(FSObject *object, Folder *dest);

private:
	Folder *dest;

};


#endif //DZ3_MOVE_H
