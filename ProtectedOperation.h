#ifndef DZ3_PROTECTEDOPERATION_H
#define DZ3_PROTECTEDOPERATION_H


#include "FSOperation.h"
#include "AccessDescriptor.h"

class ProtectedOperation : public FSOperation {
public:
	ProtectedOperation(FSOperation *wrappedOperation);

	void execute() override;

protected:
	bool checkPrecondition();

private:
	FSOperation *wrappedOperation;
};


#endif //DZ3_PROTECTEDOPERATION_H
