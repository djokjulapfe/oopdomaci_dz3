#include "Filesystem.h"
#include "AccessException.h"
#include "NameCollisionException.h"
#include "ListDirectory.h"
#include "WriteFile.h"
#include "WriteFailedException.h"
#include "CopyPaste.h"
#include "DeleteObject.h"
#include "SizeCalculatorVisitor.h"
#include "AccessVisitor.h"

Filesystem::Filesystem(unsigned capacity) {
	Filesystem::capacity = capacity;
	root = new Folder("/");
}

void Filesystem::createFile(std::string fName, Folder *parentFolder) {
	CreateFile createFile(parentFolder, fName);
	ProtectedOperation po(&createFile);
	try {
		po.execute();
	} catch (AccessException &e) {
		throw AccessException("No access", &e);
	} catch (NameCollisionException &e) {
		throw NameCollisionException("Same name", &e);
	}
}

void Filesystem::createFolder(std::string fName, Folder *parentFolder) {
	CreateFolder createFolder(parentFolder, fName);
	ProtectedOperation po(&createFolder);
	try {
		po.execute();
	} catch (AccessException &e) {
		throw AccessException("No access", &e);
	}
}

std::vector<FSObject *> Filesystem::listFolder(Folder *f) {
	ListDirectory listDirectory(f);
	ProtectedOperation po(&listDirectory);
	try {
		po.execute();
		return listDirectory.objs;
	} catch (AccessException &e) {
		throw AccessException("No access", &e);
	} catch (NameCollisionException &e) {
		throw NameCollisionException("Same name", &e);
	}
}

std::vector<byte> Filesystem::readFile(File *file) {
	ReadFile readFile(file);
	ProtectedOperation po(&readFile);
	try {
		po.execute();
		return readFile.data;
	} catch (AccessException &e) {
		throw AccessException("No access", &e);
	} catch (NameCollisionException &e) {
		throw NameCollisionException("Same name", &e);
	}
}

void Filesystem::writeFile(File *file, std::vector<byte> content) {
	WriteFile writeFile(file, content);
	ProtectedOperation po(&writeFile);
	try {
		if (this->freeSpace() < content.size()) throw WriteFailedException("No space left", nullptr);
		po.execute();
	} catch (AccessException &e) {
		throw AccessException("No access", &e);
	} catch (WriteFailedException &e) {
		throw WriteFailedException("No space left", &e);
	}
}

void Filesystem::grantAccess(FSObject *fObj, std::string opName) {
	fObj->getAccessDescriptor()->add(opName);
}

void Filesystem::revokeAccess(FSObject *fObj, std::string opName) {
	fObj->getAccessDescriptor()->remove(opName);
}

Folder *Filesystem::openFolder(std::string folderPath) {
	std::vector<std::string> dirs = split(folderPath);
	Folder *it = root;
	for (const auto &dir : dirs) {
		auto itobj = it->getObjects();
		it = nullptr;
		for (auto &&item : itobj) {
			if (item->getName() == dir && item->isFolder()) {
				it = (Folder *) item;
				break;
			}
		}
		if (it == nullptr) break;
	}
	return it;
}

std::vector<FSObject *> Filesystem::search(std::string objectName) {
	Search search(root, objectName);
	ProtectedOperation po(&search);
	try {
		po.execute();
		return search.result;
	} catch (AccessException &e) {
		throw AccessException("This should not appear!", &e);
	}
}

void Filesystem::copyPaste(FSObject *objToCopy, Folder *destFolder, std::string newName) {
	CopyPaste copyPaste(objToCopy, destFolder, newName);
	ProtectedOperation po(&copyPaste);
	try {
		auto *sizeCalculatorVisitor = new SizeCalculatorVisitor();
		objToCopy->accept(*sizeCalculatorVisitor);
		auto tsize = sizeCalculatorVisitor->getSize();
		delete sizeCalculatorVisitor;
		if (freeSpace() - tsize < 0) {
			throw WriteFailedException("Not enough space", nullptr);
		}
		for (auto &&item : destFolder->getObjects()) {
			if (item->getName() == newName) throw NameCollisionException("Same name", nullptr);
		}
		po.execute();
	} catch (AccessException &e) {
		throw AccessException("No access", &e);
	} catch (NameCollisionException &e) {
		throw NameCollisionException("Same name", &e);
	} catch (WriteFailedException &e) {
		throw WriteFailedException("Not enough space", &e);
	}
}

void Filesystem::move(FSObject *objToMove, Folder *destFolder) {
	Move move(objToMove, destFolder);
	ProtectedOperation po(&move);
	try {
		for (auto &&item : destFolder->getObjects()) {
			if (item->getName() == objToMove->getName()) throw NameCollisionException("Same name", nullptr);
		}
		po.execute();
	} catch (AccessException &e) {
		throw AccessException("No access", &e);
	} catch (NameCollisionException &e) {
		throw NameCollisionException("Same name", &e);
	}
}

void Filesystem::deleteObject(FSObject *objToDelete) {
	AccessVisitor accessVisitor("DeleteObject");
	objToDelete->accept(accessVisitor);
	DeleteObject deleteObject(objToDelete);
	ProtectedOperation po(&deleteObject);
	try {
		if (accessVisitor.isAccessible()) {
			po.execute();
		} else {
			throw AccessException("Some files might be -DeleteObject", nullptr);
		}
	} catch (AccessException &e) {
		throw AccessException("No access", &e);
	}
}

long Filesystem::freeSpace() {
	SizeCalculatorVisitor sizeCalculatorVisitor;
	root->accept(sizeCalculatorVisitor);
	return capacity - sizeCalculatorVisitor.getSize();
}

Folder *Filesystem::getRoot() const {
	return root;
}

std::vector<std::string> Filesystem::split(std::string s) {
	if (s[s.length() - 1] != '/') s.append("/");
	//if (s[s.length() - 1] == '/') s.erase(s.length()-1, 1);
	std::vector<std::string> ret;
	std::string delimiter = "/";
	std::string token;
	size_t pos = 0;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		ret.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	return ret;
}
