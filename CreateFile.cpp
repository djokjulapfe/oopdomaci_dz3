#include "CreateFile.h"

void CreateFile::execute() {
	f->add(new File(filename));
}

CreateFile::CreateFile(Folder *f, const std::string &filename) : f(f), filename(filename) {
}
