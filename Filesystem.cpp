#include "Filesystem.h"

void Filesystem::createFile(std::string fName, Folder *parentFolder) {
	// TODO: implement
}

void Filesystem::createFolder(std::string fName, Folder *parentFolder) {
	// TODO: implement
}

std::vector<FSObject *> Filesystem::listFolder() {
	// TODO: implement
	return std::vector<FSObject *>();
}

std::vector<byte> Filesystem::readFlie(File *file) {
	// TODO: implement
	return std::vector<byte>();
}

void Filesystem::writeFile(std::vector<byte> content) {
	// TODO: implement
}

void Filesystem::grantAccess(FSObject *fObj, std::string opName) {
	// TODO: implement
}

void Filesystem::revokeAccess(FSObject *fObj, std::string opName) {
	// TODO: implement
}

Folder *Filesystem::openFolder(std::string folderPath) {
	// TODO: implement
	return nullptr;
}

std::vector<FSObject *> Filesystem::search(std::string objectName) {
	// TODO: implement
	return std::vector<FSObject *>();
}

void Filesystem::copyPaste(FSObject *objToCopy, Folder *destFolder, std::string newName) {
	// TODO: implement
}

void Filesystem::move(FSObject *objToMove, Folder *destFolder) {
	// TODO: implement
}

void Filesystem::deleteFile(FSObject *objToDelete) {
	// TODO: implement
}

long Filesystem::freeSpace() {
	// TODO: implement
	return 0;
}
