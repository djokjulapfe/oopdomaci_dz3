#ifndef DZ3_FSVISITOR_H
#define DZ3_FSVISITOR_H


#include "File.h"
#include "Folder.h"

class FSVisitor {
public:

	virtual void visitFile(File f);

	virtual void visitFolder(Folder f);
};


#endif //DZ3_FSVISITOR_H
