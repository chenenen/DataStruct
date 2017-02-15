#include"BRTree.h"
int main()
{
	int i = 0;
	BRTree<int,int> brt1;
	//int a[8] = {5,1,2,3,7,0,9,4};
	int a[12] = {5,1,2,12,11,10,4,9,7,8,15,0};
	for(i = 0; i <sizeof(a)/sizeof(a[0]); i++)
	{
		brt1.Insert(a[i],i);
		cout<<a[i];
		cout<<"IsBRTree?"<<brt1.IsBRTree()<<endl;
	}
	brt1.InOrder();
	return 0;
}


//小结：
出现问题的地方
1）单旋之后的颜色更改问题
2）双旋之后的颜色更改问题
