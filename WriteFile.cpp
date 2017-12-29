#include "WriteFile.h"
#include "FSException.h"

WriteFile::WriteFile(FSObject *object, const std::vector<byte> &data) : FSOperation(object), data(data) {
	if (object->isFolder()) throw FSException("Object is not a file", nullptr);
	opName = "WriteFile";
}

void WriteFile::execute() {
	auto *file = (File*) object;
	file->write(data);
}
