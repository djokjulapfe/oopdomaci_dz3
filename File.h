#ifndef DZ3_FILE_H
#define DZ3_FILE_H


#include "FSObject.h"
#include "FSVisitor.h"
#include "AccessDescriptor.h"

using byte = unsigned char;

class File : public FSObject {
public:
	explicit File(const std::string &name);

	File();

	void accept(FSVisitor &v) override;

	long size() override;

	FSObject *copy() override;

	void write(std::vector<byte> content);

	std::vector<byte> &read();

private:
	std::vector<byte> data;
};


#endif //DZ3_FILE_H
