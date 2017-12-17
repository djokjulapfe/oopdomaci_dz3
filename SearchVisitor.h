#ifndef DZ3_SEARCHVISITOR_H
#define DZ3_SEARCHVISITOR_H


#include "FSVisitor.h"

class SearchVisitor : public FSVisitor {
public:
	void visitFile(File f) override;

	void visitFolder(Folder f) override;

private:
	std::vector<FSObject*> foundObjects;
};


#endif //DZ3_SEARCHVISITOR_H
