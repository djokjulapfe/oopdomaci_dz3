#include <iostream>
#include "Filesystem.h"
#include "SearchVisitor.h"
#include "ReadFile.h"
#include "Search.h"
#include "ProtectedOperation.h"
#include "AccessException.h"
#include "CreateFile.h"

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

/**
 * How to use:
 * TraversVisitor tv(root);
 * where root is of type Folder *
 *
 * When the program is run you can give it 3 comands:
 * k - index of the object you want to move to
 * .. - move to the parent of the current folder
 * q/. - exit the visitor
 */

class TraversVisitor : public FSVisitor {
public:
	explicit TraversVisitor(Folder *currLocation) : currLocation(currLocation) {
		currLocation->accept(*this);
		int k = 0;
		while (k != -2) {
			std::string in;
			std::cin >> in;

			if (in == "echo") {
				std::cin >> in;
				std::cout << in << std::endl;
			} if (in == "touch") {
				std::cin >> in; //folder name
				currLocation->add(new File(in));
			} else if (in == "mkdir") {
				std::cin >> in; //folder name
				currLocation->add(new Folder(in));
			} else if (in == "q" || in == ".") {
				k = -2;
			} else if (in == "..") {
				k = -1;
				this->move(k);
			} else {
				k = std::atoi(in.c_str());
				this->move(k);
			}
		}
	}

	void visitFile(File &f) override {
		std::cout << "File: " << f.getName() << ": ";
		printArray(f.read());
	}

	void visitFolder(Folder &f) override {

		int i = 0;
		for (auto &&item :f.getObjects()) {
			std::cout << i++ << " " << item->getName() << std::endl;
		}
	}

	void move(const int &k) {
		if (k == -1) {
			if (currLocation->parent == nullptr) {
				std::cout << "You are in /!\n";
			} else {
				currLocation = currLocation->parent;
			}
		} else {
			if (k >= currLocation->getObjects().size()) {
				std::cout << "There are not that many objects in this directory!\n";
			} else if (dynamic_cast<Folder *>(currLocation->getObjects()[k]) != nullptr) {
				currLocation = (Folder *) currLocation->getObjects()[k];
			} else {
				File * f = (File *) currLocation->getObjects()[k];
				std::cout << "File: " << f->getName() << ": ";
				printArray(f->read());
			}
		}
		currLocation->accept(*this);
	}

private:
	Folder *currLocation;
};

void test1() {
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
	readFile->execute();
	printArray(readFile->data);
	delete readFile;

	readFile = new ReadFile(*(File *) searchVisitor->foundObjects[1]);
	readFile->execute();
	printArray(readFile->data);
	delete readFile;

	readFile = new ReadFile(*(File *) searchVisitor->foundObjects[2]);

	readFile->execute();
	printArray(readFile->data);
	((File *) searchVisitor->foundObjects[2])->write(std::vector<byte>{1, 2, 3});


	readFile->execute();
	printArray(readFile->data);
	delete readFile;

	readFile = new ReadFile(*(File *) noaccess->getObjects()[1]);
	readFile->execute();
	printArray(readFile->data);

	delete readFile;

	auto *search = new Search(root, "pera.txt");
	search->execute();
	std::cout << search->result.size() << std::endl;
	delete search;

	search = new Search(noaccess, "pera.txt");
	search->execute();
	std::cout << search->result.size() << std::endl;
	delete search;
	search = new Search(noaccess, "pera.txt");

	auto *protectedOperation = new ProtectedOperation(search);
	try {
		protectedOperation->execute();
		std::cout << search->result.size() << std::endl;
	} catch (AccessException &e) {
		std::cout << e.what();
	}
	delete protectedOperation;
	delete search;

	search = new Search(root, "pera.txt");
	protectedOperation = new ProtectedOperation(search);
	try {
		protectedOperation->execute();
		std::cout << search->result.size() << std::endl;
	} catch (AccessException &e) {
		std::cout << e.what();
	}
	delete protectedOperation;
	delete search;

	auto *createFile = new CreateFile(root, "pera.txt");

	search = new Search(root, "pera.txt");
	search->execute();
	std::cout << search->result.size() << std::endl;
	createFile->execute();
	search->execute();
	std::cout << search->result.size() << std::endl;

	delete createFile;
	delete search;
	delete searchVisitor;

	TraversVisitor traversVisitor(root);

	delete root;
}

int main() {
	test1();
	return 0;
}
