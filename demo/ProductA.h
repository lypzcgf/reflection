#pragma once

#include "BaseProduct.h"


class ProductA :public BaseProduct
{
	DECLARE_MANAGER_SIMPLEFACTORY(ProductA, BaseProduct)
public:
	void show();
};

