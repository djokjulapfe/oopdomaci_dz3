#ifndef DZ3_SEARCHVISITOR_H
#define DZ3_SEARCHVISITOR_H


#include <iostream>
#include "FSVisitor.h"
#include "FSObject.h"
#include "Folder.h"
#include "File.h"

class SearchVisitor : public FSVisitor {
public:
	SearchVisitor(const std::string &filename);

	std::vector<FSObject *> foundObjects;

	void visitFile(File &f) override;

	void visitFolder(Folder &f) override;

private:
	std::string filename;
};


#endif //DZ3_SEARCHVISITOR_H
