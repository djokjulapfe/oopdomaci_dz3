#include "Search.h"
#include "SearchVisitor.h"
#include "AccessException.h"

void Search::execute() {
	if (root->getAccessDescriptor()->checkAccess("ReadFile")) {
		SearchVisitor *searchVisitor = new SearchVisitor(filename);
		root->accept(*searchVisitor);
		result = searchVisitor->foundObjects;
		delete searchVisitor;
	} else {
		throw AccessException("Ne moze!", nullptr);
	}
}

Search::Search(Folder *root, const std::string &filename) : root(root), filename(filename) {
	opName = "Search";
}


