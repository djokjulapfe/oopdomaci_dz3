#ifndef DZ3_READFILE_H
#define DZ3_READFILE_H


#include "FSOperation.h"
#include "File.h"

class ReadFile : public FSOperation {
public:
	explicit ReadFile(File *f);

	void execute() override;

	std::vector<byte> data;

private:
	File *f;
};


#endif //DZ3_READFILE_H
