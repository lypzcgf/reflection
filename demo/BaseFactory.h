#pragma once

class BaseProduct;

class BaseFactory
{
public:
	virtual BaseProduct* AcquireProduct() = 0;
	virtual void ReleaseProduct(BaseProduct *bp) = 0;
protected:
	BaseFactory();
	virtual ~BaseFactory();
private:
	BaseFactory(const BaseFactory &src);
	BaseFactory & operator=(const BaseFactory &rhs);
};

