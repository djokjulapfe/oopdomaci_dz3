#include "Search.h"
#include "SearchVisitor.h"

void Search::execute() {

	auto *searchVisitor = new SearchVisitor(filename);
	object->accept(*searchVisitor);
	result = searchVisitor->foundObjects;
	delete searchVisitor;

}

Search::Search(Folder *root, const std::string &filename) : FSOperation(root), filename(filename) {
	opName = "Search";
}


