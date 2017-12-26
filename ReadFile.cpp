#include "ReadFile.h"

void ReadFile::execute() {
	data = f->read();
}

ReadFile::ReadFile(File &f) : f(&f) {
	opName = "ReadFile";
}
