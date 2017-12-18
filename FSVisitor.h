#ifndef DZ3_FSVISITOR_H
#define DZ3_FSVISITOR_H

class File;
class Folder;

class FSVisitor {
public:

	virtual void visitFile(File &f) = 0;

	virtual void visitFolder(Folder &f) = 0;
};


#endif //DZ3_FSVISITOR_H
