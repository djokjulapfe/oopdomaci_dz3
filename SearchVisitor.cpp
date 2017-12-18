#include "SearchVisitor.h"

void SearchVisitor::visitFile(File &f) {

}

void SearchVisitor::visitFolder(Folder &f) {
	for (auto &&item : f.getObjects()) {
		item->accept(*this);
	}
}
