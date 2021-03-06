// demo.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
//
//
//int main()
//{
//    return 0;
//}

#include "BaseProduct.h"



void main()
{
	int ProductID;
	int Continue;
	while (true)
	{
		cout << "input Product ID which you want to use(exit=0)" << endl;
		cin >> ProductID;
		if (0 == ProductID)
			return;

		BaseProduct *bp = ShoppingMall<int,BaseProduct>::AcquireProduct(ProductID);

		if (bp != NULL)
			bp->show();//显示产品名
		else
		{
			cout << "Product can't find." << endl;
			cout << "Do you want to find something else?(NO=0/yes=other)" << endl;
			cin >> Continue;
			if (0 == Continue)
				return;
			else
				continue;
		}

		ShoppingMall<int,BaseProduct>::ReleaseProduct(ProductID,bp);
	}
}


