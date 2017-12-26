#ifndef DZ3_SEARCH_H
#define DZ3_SEARCH_H


#include "FSOperation.h"

class Search : public FSOperation {
public:

	Search(Folder *root, const std::string &filename);

	void execute() override;

	std::vector<FSObject *> result;

private:
	std::string filename;
};


#endif //DZ3_SEARCH_H
