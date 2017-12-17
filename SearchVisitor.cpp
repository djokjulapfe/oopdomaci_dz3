#include "SearchVisitor.h"

void SearchVisitor::visitFile(File f) {
	FSVisitor::visitFile(f);
}

void SearchVisitor::visitFolder(Folder f) {
	FSVisitor::visitFolder(f);
}
