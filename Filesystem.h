#ifndef DZ3_FILESYSTEM_H
#define DZ3_FILESYSTEM_H


#include "Folder.h"

using byte = unsigned char;

class Filesystem {
public:

	Filesystem &Instance() {
		static Filesystem instance;
		return instance;
	}

	Filesystem(const Filesystem &) = delete;

	Filesystem(Filesystem &&) = delete;

	void createFile(std::string fName, Folder parentFolder);

	void createFolder(std::string fName, Folder parentFolder);

	std::vector<FSObject *> listFolder();

	std::vector<byte> readFlie(File file);

	void writeFile(std::vector<byte> content);

	void grantAccess(FSObject *fObj, std::string opName = nullptr);

	void revokeAccess(FSObject *fObj, std::string opName = nullptr);

	Folder *openFolder(std::string folderPath);

	std::vector<FSObject *> search(std::string objectName);

	void copyPaste(FSObject objToCopy, Folder destFolder, std::string newName);

	void move(FSObject objToMove, Folder destFolder);

	void deleteFile(FSObject objToDelete);

	long freeSpace();


private:

	Filesystem() = default;

	Folder *root;
};


#endif //DZ3_FILESYSTEM_H
