#include "ReadFile.h"
#include "AccessException.h"

void ReadFile::execute() {
	if (f->getAccessDescriptor()->checkAccess(opName)) {
		data = f->read();
	} else {
		throw AccessException("Can't read file", nullptr);
	}
}

ReadFile::ReadFile(File &f) : f(&f) {
	opName = "ReadFile";
}
