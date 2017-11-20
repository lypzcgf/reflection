#pragma once

#include "BaseProduct.h"


class ProductB :public BaseProduct
{
	DECLARE_MANAGER_SIMPLEFACTORY(ProductB, BaseProduct)
public:
	void show();
};

