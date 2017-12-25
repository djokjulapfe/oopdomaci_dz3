#include <iostream>
#include "Filesystem.h"
#include "SearchVisitor.h"
#include "ReadFile.h"
#include "Search.h"
#include "AccessException.h"

using byte = unsigned char;

void ident(int depth) {
	for (int i = 0; i < depth; ++i) {
		std::cout << "\t";
	}
}

void printArray(std::vector<byte> vector) {
	if (vector.size() > 10) {
		std::cout << (int) vector[0] << " ";
		std::cout << (int) vector[1] << " ";
		std::cout << "... ";
		std::cout << (int) vector[vector.size() - 2] << " ";
		std::cout << (int) vector[vector.size() - 1] << " ";
	} else {
		for (auto &&item : vector) {
			std::cout << (int) item << " ";
		}
	}
	std::cout << std::endl;
}

static int depth = 0;

class PrintVisitor : public FSVisitor {
public:
	void visitFile(File &f) override {

		ident(depth);
		std::cout << "File: " << f.getName() << ": ";
		printArray(f.read());

	}

	void visitFolder(Folder &f) override {

		ident(depth);
		std::cout << "Folder: " << f.getName() << " {\n";
		depth++;

		for (auto &&object :f.getObjects()) {
			object->accept(*this);
		}

		depth--;
		ident(depth);
		std::cout << "}\n";
	}
};

void test1() {

	// FSObject

	File X("X"), Y("Y"), Z("Z");

	X.write(std::vector<byte>{1, 2, 3, 4});
	X.write(std::vector<byte>{1, 2, 3, 4});
	X.write(std::vector<byte>{1, 2, 3, 4});

	Y.write(std::vector<byte>{4, 3, 2, 1});
	Y.write(std::vector<byte>{4, 3, 2, 1});
	Y.write(std::vector<byte>{4, 3, 2, 1});

	Z.write(std::vector<byte>{1, 1, 1, 1});
	Z.write(std::vector<byte>{1, 1, 1, 1});
	Z.write(std::vector<byte>{1, 1, 1, 1});

	Folder A("A");
	Folder B("Z");
	Folder C("C");

	A.add(&X);
	A.add(&B);

	B.add(&Y);
	B.add(&C);

	C.add(&Z);

	FSVisitor *printVisitor = new PrintVisitor();
	A.accept(*printVisitor);
	delete printVisitor;

	// AccessDescriptor
	X.accessDescriptor->add("ReadFile");
	Y.accessDescriptor->add("ReadFile");
	Z.accessDescriptor->add("ReadFile");

	A.accessDescriptor->add("ReadFile");
	B.accessDescriptor->add("ReadFile");
	C.accessDescriptor->add("ReadFile");

	// SearchVisitor

	SearchVisitor *searchVisitor = new SearchVisitor("Z");
	A.accept(*searchVisitor);
	std::cout << searchVisitor->foundObjects.size() << std::endl;

	B.accessDescriptor->remove("ReadFile");

	searchVisitor->foundObjects.clear();
	A.accept(*searchVisitor);
	std::cout << searchVisitor->foundObjects.size() << std::endl;

	delete searchVisitor;
}

void test2() {
	Folder *root = new Folder("/");
	Folder *noaccess;
	root->getAccessDescriptor()->add("ReadFile");
	{
		Folder *usr = new Folder("usr");
		Folder *lib = new Folder("lib");
		Folder *java = new Folder("java");
		Folder *tmp = new Folder("tmp");
		Folder *pera = new Folder("pera");
		Folder *dev = new Folder("dev");
		Folder *home = new Folder("home");
		home->getAccessDescriptor()->add("ReadFile");
		Folder *djokjula = new Folder("djokjula");
		djokjula->getAccessDescriptor()->add("ReadFile");
		Folder *dDocuments = new Folder("Documents");
		dDocuments->getAccessDescriptor()->add("ReadFile");
		Folder *dWork = new Folder("work");
		dWork->getAccessDescriptor()->add("ReadFile");
		Folder *dDownloads = new Folder("Downloads");
		dDownloads->getAccessDescriptor()->add("ReadFile");
		Folder *gpu = new Folder("gpu");
		gpu->getAccessDescriptor()->add("ReadFile");
		Folder *gDocuments = new Folder("Documents");
		gDocuments->getAccessDescriptor()->add("ReadFile");

		root->add(usr);
		root->add(tmp);
		root->add(dev);
		root->add(home);

		usr->add(lib);
		usr->add(java);

		tmp->add(pera);
		for (int i = 0; i < 10; ++i) {
			auto *tfile = new File;
			std::vector<byte> tmpVector;
			for (int j = 0; j < 1024; ++j) {
				tmpVector.push_back((byte) rand());
			}
			tfile->write(tmpVector);
			tfile->getAccessDescriptor()->add("ReadFile");
			tmp->add(tfile);
		}

		for (int i = 0; i < 10; ++i) {
			std::string fname = "tty";
			fname.append(std::to_string(i));
			auto *tfile = new File(fname);
			std::vector<byte> tmpVector;
			for (int j = 0; j < 1024; ++j) {
				tmpVector.push_back((byte) rand());
			}
			tfile->write(tmpVector);
			tfile->getAccessDescriptor()->add("ReadFile");
			dev->add(tfile);
		}
		noaccess = dev;

		home->add(djokjula);
		home->add(gpu);

		djokjula->add(dDocuments);
		djokjula->add(dDownloads);
		File *tfile = new File("pera.png");
		tfile->write(std::vector<byte>{'S', 'l', 'i', 'k', 'a'});
		tfile->getAccessDescriptor()->add("ReadFile");
		djokjula->add(tfile);

		tfile = new File("pera.txt");
		tfile->write(std::vector<byte>{'Z', 'd', 'r', 'a', 'v', 'o'});
		tfile->getAccessDescriptor()->add("ReadFile");
		dDocuments->add(tfile);
		dDocuments->add(dWork);

		tfile = new File("pera.txt");
		tfile->write(std::vector<byte>{'s', 't', 'a'});
		tfile->getAccessDescriptor()->add("ReadFile");
		dWork->add(tfile);

		tfile = new File("pera.txt");
		tfile->write(std::vector<byte>{'I', 'm', 'a'});
		tfile->getAccessDescriptor()->add("ReadFile");
		dDownloads->add(tfile);

		tfile = new File("pera(2).txt");
		tfile->write(std::vector<byte>{'i', 'm', 'a'});
		tfile->getAccessDescriptor()->add("ReadFile");
		dDownloads->add(tfile);

		gpu->add(gDocuments);

		tfile = new File("pera.txt");
		tfile->write(std::vector<byte>{'t', 'e', 'b', 'r', 'a'});
		tfile->getAccessDescriptor()->add("ReadFile");
		gDocuments->add(tfile);
		gDocuments->add(new Folder("pera"));
	}

	auto *printVisitor = new PrintVisitor();
	root->accept(*printVisitor);
	delete printVisitor;

	auto *searchVisitor = new SearchVisitor("pera.txt");
	root->accept(*searchVisitor);
	std::cout << searchVisitor->foundObjects.size() << std::endl;

	// Read File

	auto *readFile = new ReadFile(*(File *) searchVisitor->foundObjects[0]);
	try {
		readFile->execute();
		printArray(readFile->data);
	} catch (AccessException &e) {
		std::cout << e.what();
	}
	delete readFile;

	readFile = new ReadFile(*(File *) searchVisitor->foundObjects[1]);
	try {
		readFile->execute();
		printArray(readFile->data);
	} catch (AccessException &e) {
		std::cout << e.what();
	}
	delete readFile;

	readFile = new ReadFile(*(File *) searchVisitor->foundObjects[2]);

	try {
		readFile->execute();
		printArray(readFile->data);
		((File *) searchVisitor->foundObjects[2])->write(std::vector<byte>{1, 2, 3});
	} catch (AccessException &e) {
		std::cout << e.what();
	}

	try {
		readFile->execute();
		printArray(readFile->data);
	} catch (AccessException &e) {
		std::cout << e.what();
	}
	delete readFile;

	auto *search = new Search(root, "pera.txt");
	try {
		search->execute();
		std::cout << search->result.size() << std::endl;
	} catch (AccessException &e) {
		std::cout << e.what();
	}
	delete search;

	search = new Search(noaccess, "pera.txt");
	try {
		search->execute();
		std::cout << search->result.size() << std::endl;
	} catch (AccessException &e) {
		std::cout << e.what();
	}
	delete search;

	delete searchVisitor;
	delete root;
}

// FSVisitor

int main() {
	//test1();
	test2();
	return 0;
}
