#ifndef DZ3_FILESYSTEM_H
#define DZ3_FILESYSTEM_H


#include "Folder.h"
#include "File.h"
#include "CreateFile.h"
#include "CreateFolder.h"
#include "Move.h"
#include "Search.h"
#include "ReadFile.h"
#include "ProtectedOperation.h"

using byte = unsigned char;

class Filesystem {
public:

	static Filesystem &Instance() {
		static Filesystem instance(1000);
		return instance;
	}

	Filesystem() = delete;

	Filesystem(const Filesystem &) = delete;

	Filesystem(Filesystem &&) = delete;

	void createFile(std::string fName, Folder *parentFolder);

	void createFolder(std::string fName, Folder *parentFolder);

	std::vector<FSObject *> listFolder(Folder *f);

	std::vector<byte> readFlie(File *file);

	void writeFile(File * file, std::vector<byte> content);

	void grantAccess(FSObject *fObj, std::string opName = nullptr);

	void revokeAccess(FSObject *fObj, std::string opName = nullptr);

	Folder *openFolder(std::string folderPath);

	std::vector<FSObject *> search(std::string objectName);

	void copyPaste(FSObject *objToCopy, Folder *destFolder, std::string newName);

	void move(FSObject *objToMove, Folder *destFolder);

	void deleteObject(FSObject *objToDelete);

	Folder *getRoot() const;

	long freeSpace();

	static std::vector<std::string> split(std::string s);

private:

	explicit Filesystem(unsigned capacity);

	unsigned capacity;

	Folder *root;
};


#endif //DZ3_FILESYSTEM_H
