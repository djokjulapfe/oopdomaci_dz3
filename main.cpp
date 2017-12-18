#include <iostream>
#include "Filesystem.h"

int main() {
	std::cout << "Hello, World!" << std::endl;
	Filesystem::Instance().freeSpace();
	return 0;
}
