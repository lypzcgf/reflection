#pragma once

#include <iostream>
#include <string>
#include "ShoppingMall.h"
//jia yi hang zhushi

class BaseProduct
{
public:
	virtual void show() = 0;
protected:
	BaseProduct();
	virtual ~BaseProduct();
private:
	BaseProduct(const BaseProduct &src);
	BaseProduct & operator=(const BaseProduct &rhs);
};

#define DECLARE_MANAGER_SIMPLEFACTORY(class_name,base_class_name) \
	friend class DerivedFactory<base_class_name,class_name>; \
	private: \
	class_name(); \
	~class_name(); \
	class_name(const class_name &src); \
	class_name & operator=(const class_name &rhs);

#define IMPLEMENT_MANAGER_SIMPLEFACTORY(class_name,base_class_name,ProductID) \
	static const string class_name##Name(#class_name); \
	static const int class_name##ID=ProductID; \
	static DerivedFactory<base_class_name,class_name> sF##class_name; \
	static BusinessPeople<int,base_class_name> Register##class_name(class_name##ID,((BaseFactory<base_class_name>*)(&sF##class_name))); \
	class_name::class_name() \
{ } \
	class_name::~class_name() \
{ } \


