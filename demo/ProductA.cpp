#include "ProductA.h"

IMPLEMENT_MANAGER_SIMPLEFACTORY(ProductA, BaseProduct, 1)

void ProductA::show()
{
	cout << ProductAName << endl;
}
