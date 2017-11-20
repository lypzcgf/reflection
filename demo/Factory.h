#pragma once

template <class BaseProductType>
class BaseFactory
{
public:
	virtual BaseProductType* AcquireProduct() = 0;
	virtual void ReleaseProduct(BaseProductType *bp) = 0;
protected:
	BaseFactory();
	virtual ~BaseFactory();
private:
	BaseFactory(const BaseFactory<BaseProductType> &src);
	BaseFactory<BaseProductType> & operator=(const BaseFactory<BaseProductType> &rhs);
};

template <class BaseProductType>
BaseFactory<BaseProductType>::BaseFactory()
{
}

template <class BaseProductType>
BaseFactory<BaseProductType>::~BaseFactory()
{
}

template <class BaseProductType, class DerivedProductType>
class Factory : public BaseFactory<BaseProductType>
{
public:
	Factory();
	~Factory();

	BaseProductType* AcquireProduct();
	void ReleaseProduct(BaseProductType *bp);

private:
	Factory(const Factory<BaseProductType, DerivedProductType>& src);
	Factory<BaseProductType, DerivedProductType> & operator=(const Factory<BaseProductType, DerivedProductType> &rhs);
};

template <class BaseProductType, class DerivedProductType>
Factory<BaseProductType, DerivedProductType>::Factory()
{
}

template <class BaseProductType, class DerivedProductType>
Factory<BaseProductType, DerivedProductType>::~Factory()
{
}

template <class BaseProductType, class DerivedProductType>
BaseProductType* Factory<BaseProductType, DerivedProductType>::AcquireProduct()
{
	BaseProductType *bp = new DerivedProductType;
	return bp;
}

template <class BaseProductType, class DerivedProductType>
void Factory<BaseProductType, DerivedProductType>::ReleaseProduct(BaseProductType *bp)
{
	delete ((DerivedProductType*)bp);
}

