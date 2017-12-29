#include "AccessVisitor.h"

AccessVisitor::AccessVisitor(const std::string &opName) : opName(opName), accessible(accessible) {
	accessible = true;
}

bool AccessVisitor::isAccessible() const {
	return accessible;
}

void AccessVisitor::visitFile(File &f) {
	accessible = f.getAccessDescriptor()->checkAccess(opName);
}

void AccessVisitor::visitFolder(Folder &f) {
	accessible = f.getAccessDescriptor()->checkAccess(opName);
	if (accessible) {
		for (auto &&item : f.getObjects()) {
			item->accept(*this);
			if (!accessible) break;
		}
	}
}
