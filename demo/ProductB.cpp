#include "ProductB.h"

IMPLEMENT_MANAGER_SIMPLEFACTORY(ProductB, BaseProduct, 2)

void ProductB::show()
{
	cout << ProductBName << endl;
}
