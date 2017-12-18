#ifndef DZ3_FILE_H
#define DZ3_FILE_H


#include "FSObject.h"
#include "FSVisitor.h"

using byte = unsigned char;

class File : public FSObject {
public:
	void accept(FSVisitor &v) override;

	long size() override;

	FSObject *copy() override;

	void write(std::vector<byte *> content);

	std::vector<byte *> read();

private:
	std::string path;
	std::vector<byte *> data;
};


#endif //DZ3_FILE_H
