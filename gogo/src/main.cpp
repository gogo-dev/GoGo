#include <cstdlib>
#include <boost/cstdint.hpp>
#include "TestClass.h"
#include "Structures.h"

using namespace boost;

int main()
{
	AccountInfo* accInfo = new AccountInfo;
	accInfo->AccountAccess = UG_ADMINISTRATOR;
	return 0;
}
