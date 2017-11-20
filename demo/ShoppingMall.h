#pragma once

#include <map>
using namespace std;

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
class DerivedFactory : public BaseFactory<BaseProductType>
{
public:
	DerivedFactory();
	~DerivedFactory();

	BaseProductType* AcquireProduct();
	void ReleaseProduct(BaseProductType *bp);

private:
	DerivedFactory(const DerivedFactory<BaseProductType, DerivedProductType>& src);
	DerivedFactory<BaseProductType, DerivedProductType> & operator=(const DerivedFactory<BaseProductType, DerivedProductType> &rhs);
};

template <class BaseProductType, class DerivedProductType>
DerivedFactory<BaseProductType, DerivedProductType>::DerivedFactory()
{
}

template <class BaseProductType, class DerivedProductType>
DerivedFactory<BaseProductType, DerivedProductType>::~DerivedFactory()
{
}

template <class BaseProductType, class DerivedProductType>
BaseProductType* DerivedFactory<BaseProductType, DerivedProductType>::AcquireProduct()
{
	BaseProductType *bp = new DerivedProductType;
	return bp;
}

template <class BaseProductType, class DerivedProductType>
void DerivedFactory<BaseProductType, DerivedProductType>::ReleaseProduct(BaseProductType *bp)
{
	delete ((DerivedProductType*)bp);
}

template<typename KeyType, class BaseProductType>
class BusinessPeople
{
public:
	BusinessPeople(const KeyType &ProductID, BaseFactory<BaseProductType> *bf);
	~BusinessPeople();
private:
	KeyType m_ProductID;
};

template<typename KeyType, class BaseProductType>
BusinessPeople<KeyType, BaseProductType>::BusinessPeople(const KeyType &ProductID, BaseFactory<BaseProductType> *bf)
{
	m_ProductID = ProductID;
	ShoppingMall<KeyType,BaseProductType>::Register(m_ProductID, bf);
}

template<typename KeyType, class BaseProductType>
BusinessPeople<KeyType, BaseProductType>::~BusinessPeople()
{
	ShoppingMall<KeyType,BaseProductType>::UnRegister(m_ProductID);
}

template<typename KeyType,class BaseProductType>
class ShoppingMall
{
public:
	static bool Register(const KeyType &ProductID, BaseFactory<BaseProductType> *bf);
	static bool UnRegister(const KeyType &ProductID);

	static BaseProductType* AcquireProduct(const KeyType &ProductID);
	static void ReleaseProduct(const KeyType &ProductID, BaseProductType *bp);

private:
	typedef map<const KeyType, BaseFactory<BaseProductType>*> AssocMap;
	static AssocMap ProductMap;

	ShoppingMall();
	~ShoppingMall();
	ShoppingMall(const ShoppingMall &src);
	ShoppingMall& operator=(const ShoppingMall &rhs);
};

template<typename KeyType, class BaseProductType>
typename ShoppingMall<KeyType, BaseProductType>::AssocMap ShoppingMall<KeyType, BaseProductType>::ProductMap;

template<typename KeyType, class BaseProductType>
bool ShoppingMall<KeyType, BaseProductType>::Register(const KeyType &ProductID, BaseFactory<BaseProductType> *bf)
{
	return ProductMap.insert((AssocMap::value_type(ProductID, bf))).second;
}

template<typename KeyType, class BaseProductType>
bool ShoppingMall<KeyType, BaseProductType>::UnRegister(const KeyType &ProductID)
{
	return (ProductMap.erase(ProductID) == 1);
}

template<typename KeyType, class BaseProductType>
BaseProductType* ShoppingMall<KeyType, BaseProductType>::AcquireProduct(const KeyType &ProductID)
{
	typename AssocMap::iterator it = ProductMap.find(ProductID);
	if (it != ProductMap.end())
	{
		BaseFactory<BaseProductType> *t = it->second;
		return t->AcquireProduct();
	}
	return NULL;
}

template<typename KeyType, class BaseProductType>
void ShoppingMall<KeyType,BaseProductType>::ReleaseProduct(const KeyType &ProductID,BaseProductType *bp)
{
	typename AssocMap::iterator it = ProductMap.find(ProductID);
	if (it != ProductMap.end())
	{
		BaseFactory<BaseProductType> *t = it->second;
		t->ReleaseProduct(bp);
	}
}

