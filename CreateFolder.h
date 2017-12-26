#ifndef DZ3_CREATEFOLDER_H
#define DZ3_CREATEFOLDER_H


#include "FSOperation.h"
#include "Folder.h"

class CreateFolder : public FSOperation {

public:
	CreateFolder(FSObject *object, const std::string &foldername);

	void execute() override;

private:
	std::string foldername;
	Folder *parent;

};


#endif //DZ3_CREATEFOLDER_H
