#include "SizeCalculatorVisitor.h"

void SizeCalculatorVisitor::visitFile(File &f) {
	size += f.size();
}

void SizeCalculatorVisitor::visitFolder(Folder &f) {
	for (auto &&item :f.getObjects()) {
		item->accept(*this);
	}
}

unsigned int SizeCalculatorVisitor::getSize() const {
	return size;
}
