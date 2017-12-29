#include <iostream>
#include "Filesystem.h"
#include "SearchVisitor.h"
#include "AccessException.h"
#include "DeleteObject.h"
#include "CopyPaste.h"
#include "ListDirectory.h"

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
			}
			if (in == "touch") {
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
				File *f = (File *) currLocation->getObjects()[k];
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
	FSObject *rndObject;
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
		rndObject = tfile; // HERE IS RNDOBJECT!
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

	auto *readFile = new ReadFile((File *) searchVisitor->foundObjects[0]);
	readFile->execute();
	printArray(readFile->data);
	delete readFile;

	readFile = new ReadFile((File *) searchVisitor->foundObjects[1]);
	readFile->execute();
	printArray(readFile->data);
	delete readFile;

	readFile = new ReadFile((File *) searchVisitor->foundObjects[2]);

	readFile->execute();
	printArray(readFile->data);
	((File *) searchVisitor->foundObjects[2])->write(std::vector<byte>{1, 2, 3});
	delete searchVisitor;

	readFile->execute();
	printArray(readFile->data);
	delete readFile;

	readFile = new ReadFile((File *) noaccess->getObjects()[1]);
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

	DeleteObject *deleteObject = new DeleteObject(root->getObjects()[4]);
	deleteObject->execute();
	search->execute();
	std::cout << search->result.size() << std::endl;

	delete deleteObject;
	delete search;

	ListDirectory *listDirectory = new ListDirectory(root);
	listDirectory->execute();
	listDirectory->print();

	CreateFolder *createFolder = new CreateFolder(root, "lib32");
	createFolder->execute();
	delete createFolder;

	listDirectory->execute();
	listDirectory->print();

	CopyPaste *copyPaste = new CopyPaste(rndObject, root, "pera.txt");
	copyPaste->execute();
	delete copyPaste;

	listDirectory->execute();
	listDirectory->print();

	Move *move = new Move(rndObject, noaccess);
	move->execute();
	delete move;

	listDirectory->execute();
	listDirectory->print();

	delete listDirectory;

	//TraversVisitor traversVisitor(root);

	delete root;
}


std::string fullPath(FSObject *curr) {
	std::string ret;
	FSObject *it = curr;
	if (curr->getName() == "/") {
		return "/";
	}
	while (it->parent != nullptr) {
		ret.insert(0, it->getName());
		ret.insert(0, "/");
		it = it->parent;
	}
	return ret;
}

class Traverser {
public:
	explicit Traverser(Folder *curr) : curr(curr) {
	}

	void ls() {
		auto list = Filesystem::Instance().listFolder(curr);
		if (curr->parent != nullptr) {
			std::cout << "..\n";
		}
		for (auto &&item : list) {
			std::cout << item->getName();
			if (item->isFolder()) std::cout << "/";
			std::cout << std::endl;
		}
	}

	void cd(std::string name) {
		if (name == "..") {
			if (curr->parent != nullptr) {
				curr = curr->parent;
			} else {
				std::cout << "You are in root!";
			}
			return;
		}
		for (auto &&item : curr->getObjects()) {
			if (item->getName() == name && item->isFolder()) {
				curr = (Folder *) item;
				return;
			}
		}
		std::cout << "No folder with the name: " << name << std::endl;
	}

	void mkdir(std::string name) {
		Filesystem::Instance().createFolder(name, curr);
	}

	void rm(std::string name) {
		for (auto &&item : curr->getObjects()) {
			if (item->getName() == name) {
				Filesystem::Instance().deleteObject(item);
			}
		}
	}

	void touch(std::string name) {
		Filesystem::Instance().createFile(name, curr);
	}

	void echo(std::string name, std::vector<byte> data) {
		for (auto &&item : curr->getObjects()) {
			if (item->getName() == name && !item->isFolder()) {
				Filesystem::Instance().writeFile((File *) item, data);
				return;
			}
		}
		std::cout << "No such file\n";
	}

	void cat(std::string name) {
		for (auto &&item : curr->getObjects()) {
			if (item->getName() == name && !item->isFolder()) {
				auto data = Filesystem::Instance().readFile((File *) item);
				for (auto &&datum : data) {
					std::cout << datum;
				}
				std::cout << std::endl;
				return;
			}
		}
		std::cout << "No such file\n";
	}

	void bytes(std::string name) {
		for (auto &&item : curr->getObjects()) {
			if (item->getName() == name && !item->isFolder()) {
				auto data = Filesystem::Instance().readFile((File *) item);
				for (auto &&datum : data) {
					std::cout << (int) datum << " ";
				}
				std::cout << std::endl;
				return;
			}
		}
		std::cout << "No such file\n";
	}

	void chmod(std::string filename, std::string opName, bool add) {
		for (auto &&item : curr->getObjects()) {
			if (item->getName() == filename) {
				if (add) {
					Filesystem::Instance().grantAccess(item, opName);
				} else {
					Filesystem::Instance().revokeAccess(item, opName);
				}
				return;
			}
		}
		std::cout << "No such file or directory";
	}

	void find(std::string name) {
		for (auto &&item : Filesystem::Instance().search(name)) {
			std::cout << fullPath(item) << std::endl;
		}
	}

	FSObject *getItem(std::string dest) {
		// UNSAFE
		auto d = Filesystem::split(dest);
		FSObject *it = curr;
		while (d.size() > 0) {
			// When you give it a/b/c it will find a/c if b doesn't exist
			for (auto &&item : ((Folder *) it)->getObjects()) {
				if (item->getName() == d[0] && item->isFolder()) {
					it = item;
					break;
				}
			}
			d.erase(d.begin());
		}
		return it;
	}

	void cp(std::string src, std::string dest) {
		// UNSAFE
		auto s = getItem(src);
		Folder *d = (Folder *) getItem(dest);
		Filesystem::Instance().copyPaste(s, d, Filesystem::split(dest).back());
	}

	void move(std::string src, std::string dest) {
		// UNSAFE
		auto s = getItem(src);
		Folder *d = (Folder *) getItem(dest);
		Filesystem::Instance().move(s, d);
	}

	int doCommand() {
		std::string c;
		std::cout << "user@dz3:" << fullPath(curr) << "$ ";
		std::cin >> c;
		if (c == "ls") {
			ls();
		} else if (c == "cd") {
			std::cin >> c;
			cd(c);
		} else if (c == "mkdir") {
			std::cin >> c;
			mkdir(c);
		} else if (c == "rm") {
			std::cin >> c;
			rm(c);
		} else if (c == "exit") {
			return -1;
		} else if (c == "touch") {
			std::cin >> c;
			touch(c);
		} else if (c == "echo") {
			std::string name;
			std::cin >> name;
			std::vector<byte> b;
			int n;
			std::cin >> n;
			for (int i = 0; i < n; ++i) {
				int byte1;
				std::cin >> byte1;
				b.push_back(byte1);
			}
			echo(name, b);
		} else if (c == "cat") {
			std::cin >> c;
			cat(c);
		} else if (c == "bytes") {
			std::cin >> c;
			bytes(c);
		} else if (c == "chmod") {
			std::string name;
			std::cin >> name;
			std::cin >> c;
			bool add = c[0] == '+';
			c.erase(c.begin(), c.begin() + 1);
			chmod(name, c, add);
		} else if (c == "find") {
			std::cin >> c;
			find(c);
		} else if (c == "cp") {
			std::string src, dst;
			std::cin >> src;
			std::cin >> dst;
			cp(src, dst);
		} else {
			std::cout << "There is no command " << c << std::endl;
		}
		return 0;
	}

	Folder *curr;
};

void test2() {
	std::cout << Filesystem::Instance().freeSpace() << std::endl;
	Traverser traverser(Filesystem::Instance().getRoot());
	traverser.mkdir("home");
	traverser.mkdir("lib");
	traverser.mkdir("tmp");
	traverser.cd("home");
	traverser.mkdir("user");
	traverser.cd("user");
	traverser.mkdir("Documents");
	traverser.cd("Documents");
	traverser.touch("pera.txt");
	traverser.cd("..");
	traverser.mkdir("Downloads");
	traverser.cd("Downloads");
	traverser.touch("pera.txt");
	traverser.cd("..");
	traverser.mkdir("Pictures");
	traverser.mkdir("Music");
	traverser.touch("numbers.txt");
	traverser.echo("numbers.txt", {1, 2, 3});
	traverser.touch("text.txt");
	traverser.echo("text.txt", {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'});
	//traverser.chmod("text.txt", "ReadFile", false);
	traverser.touch("pera.txt");
	traverser.cp("text.txt", "Documents/text.txt");
	traverser.move("Documents/pera.txt", "Music");
	traverser.rm("text.txt");
	traverser.cd("Documents");
	for (int i = 0; i < 82; ++i) {
		std::string tname = "text";
		tname.append(std::to_string(i));
		tname.append(".txt");
		traverser.cp("text.txt", tname);
	}

	std::cout << Filesystem::Instance().freeSpace() << std::endl;

	auto test = Filesystem::Instance().openFolder("home/user");
	if (test == nullptr) {
		std::cout << "No such directory\n";
	} else {
		for (auto &&getObject :test->getObjects()) {
			std::cout << getObject->getName() << " ";
		}
		std::cout << std::endl;
	}

	while (traverser.doCommand() == 0);
}

int main() {
	std::cout << "\n--------Running test1----------\n\n";
	test1();
	std::cout << "\n--------Running test2----------\n\n";
	test2();
	return 0;
}
