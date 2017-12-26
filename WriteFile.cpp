#include "WriteFile.h"

WriteFile::WriteFile(FSObject *object, const std::vector<byte> &data) : FSOperation(object), data(data) {
}

void WriteFile::execute() {
	// TODO: check if object is File*
	File *file = (File*) object;
	file->write(data);
}
