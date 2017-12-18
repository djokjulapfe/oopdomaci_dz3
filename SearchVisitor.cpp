#include "SearchVisitor.h"
#include "AccessDescriptor.h"

void SearchVisitor::visitFile(File &f) {
	if (f.getName() == filepath) {
		foundObjects.push_back(&f);
	}
}

void SearchVisitor::visitFolder(Folder &f) {
	if (f.getName() == filepath) {
		foundObjects.push_back(&f);
	}
	for (auto &&item : f.getObjects()) {
		auto acc = item->getAccessDescriptor()->getAllowedOperations();
		if (std::find(acc.begin(), acc.end(), "ReadFile") == acc.end()) {
			continue;
		}
		item->accept(*this);
	}
}
