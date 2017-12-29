#ifndef DZ3_ACCESSVISITOR_H
#define DZ3_ACCESSVISITOR_H


#include "FSVisitor.h"
#include "File.h"
#include "Folder.h"
#include <string>

class AccessVisitor : public FSVisitor {
public:
	AccessVisitor(const std::string &opName);

	void visitFile(File &f) override;

	void visitFolder(Folder &f) override;

	bool isAccessible() const;

private:
	std::string opName;
	bool accessible;
};


#endif //DZ3_ACCESSVISITOR_H
