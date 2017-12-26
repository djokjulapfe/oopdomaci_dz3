#include "File.h"

void File::accept(FSVisitor &v) {
	v.visitFile(*this);
}

long File::size() {
	return data.size();
}

FSObject *File::copy() {
	auto *newFile = new File(name);
	newFile->write(this->data);
	return newFile;
}

void File::write(std::vector<byte> content) {
	for (auto &&item : content) {
		data.push_back(item);
	}
}

std::vector<byte> &File::read() {
	return data;
}

File::File(const std::string &name) : FSObject(name) {

}

File::File() : FSObject() {

}
