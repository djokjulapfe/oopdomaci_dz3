#ifndef DZ3_SIZECALCULATORVISITOR_H
#define DZ3_SIZECALCULATORVISITOR_H


#include "FSVisitor.h"
#include "File.h"
#include "Folder.h"

class SizeCalculatorVisitor : public FSVisitor {
public:
	SizeCalculatorVisitor();

	void visitFile(File &f) override;

	void visitFolder(Folder &f) override;

	unsigned int getSize() const;

private:
	unsigned size;
};


#endif //DZ3_SIZECALCULATORVISITOR_H
