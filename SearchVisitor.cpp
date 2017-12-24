#include "SearchVisitor.h"

void SearchVisitor::visitFile(File &f) {
	if (f.getName() == filename) {
		foundObjects.push_back(&f);
	}
}

void SearchVisitor::visitFolder(Folder &f) {
	if (f.getName() == filename) {
		foundObjects.push_back(&f);
	}
	auto acc = f.getAccessDescriptor()->getAllowedOperations();
	if (std::find(acc.begin(), acc.end(), "ReadFile") != acc.end()) {

		for (auto &&item : f.getObjects()) {
			item->accept(*this);
		}

	}
}

SearchVisitor::SearchVisitor(const std::string &filename) : filename(filename) {
}
