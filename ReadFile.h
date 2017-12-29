#ifndef DZ3_READFILE_H
#define DZ3_READFILE_H


#include "FSOperation.h"
#include "File.h"

class ReadFile : public FSOperation {
public:
	ReadFile(FSObject *object);

	void execute() override;

	std::vector<byte> data;

private:
};


#endif //DZ3_READFILE_H
