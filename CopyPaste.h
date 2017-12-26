#ifndef DZ3_COPYPASTE_H
#define DZ3_COPYPASTE_H


#include "FSOperation.h"
#include "Folder.h"

class CopyPaste : public FSOperation {
public:

	CopyPaste(FSObject *object, Folder *destFolder, const std::string &newName);

	void execute() override;

private:
	Folder *destFolder;
	std::string newName;

};


#endif //DZ3_COPYPASTE_H
