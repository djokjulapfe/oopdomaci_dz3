#ifndef DZ3_CREATEFILE_H
#define DZ3_CREATEFILE_H


#include "FSOperation.h"
#include "Folder.h"
#include "File.h"

class CreateFile : public FSOperation{
public:
	CreateFile(Folder *f, const std::string &filename);

	void execute() override;

private:
	Folder *f;
	std::string filename;
};


#endif //DZ3_CREATEFILE_H
