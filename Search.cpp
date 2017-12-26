#include "Search.h"
#include "SearchVisitor.h"

void Search::execute() {

	auto *searchVisitor = new SearchVisitor(filename);
	root->accept(*searchVisitor);
	result = searchVisitor->foundObjects;
	delete searchVisitor;

}

Search::Search(Folder *root, const std::string &filename) : root(root), filename(filename) {
	opName = "Search";
}


