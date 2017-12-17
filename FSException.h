#ifndef DZ3_FSEXCEPTION_H
#define DZ3_FSEXCEPTION_H

#include <string>

class FSException : public std::exception {
public:
	FSException(const std::string &msg, const FSException &cause);

	void FilesystemException(std::string msg);

	const char *what() const override;

private:
	FSException causedBy;
};


#endif //DZ3_FSEXCEPTION_H
