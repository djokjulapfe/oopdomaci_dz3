#include "File.h"

void File::accept(FSVisitor v) {
	FSObject::accept(v);
}
