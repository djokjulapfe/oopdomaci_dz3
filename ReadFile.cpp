#include "ReadFile.h"

void ReadFile::execute() {
	data = ((File *) object)->read();
}

ReadFile::ReadFile(FSObject *object) : FSOperation(object) {
	opName = "ReadFile";
}
