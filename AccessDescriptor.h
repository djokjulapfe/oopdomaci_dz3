#ifndef DZ3_ACCESSDESCRIPTOR_H
#define DZ3_ACCESSDESCRIPTOR_H

#include <string>
#include <vector>
#include <algorithm>

class AccessDescriptor {
public:
	AccessDescriptor();

	void add(std::string operationName);

	void remove(std::string operationName);

	bool checkAccess(std::string operationName);

	const std::vector<std::string> &getAllowedOperations() const;

	AccessDescriptor *copy();

private:
	std::vector<std::string> allowedOperations;
};


#endif //DZ3_ACCESSDESCRIPTOR_H
