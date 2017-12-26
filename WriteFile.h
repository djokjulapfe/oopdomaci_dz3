#ifndef DZ3_WRITEFILE_H
#define DZ3_WRITEFILE_H


#include "FSOperation.h"
#include "File.h"

class WriteFile : public FSOperation{
public:
	WriteFile(FSObject *object, const std::vector<byte> &data);

	void execute() override;

private:
	std::vector<byte> data;
};


#endif //DZ3_WRITEFILE_H
