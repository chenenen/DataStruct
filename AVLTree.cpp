#include"AVLTree.h"
void Test()
{
	AVLTree<int,int> t1;
	int a[] = {16,3,7,11,9,26,18,14,15};
	for(int i = 0; i<(sizeof(a)/sizeof(a[0])); i++)
	{
		t1.Insert(a[i],i);
	}
	t1.InOrder();
	cout<<"IsBalance: "<<t1.IsBalance()<<endl;
	

	//AVLTree<int,int> t2;
	//int a[] = {	4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
	//for(int i = 0; i<(sizeof(a)/sizeof(a[0])); i++)
	//{
	//	t2.Insert(a[i],i);
	//	//cout<<"IsBalance: "<<t2.IsBalance()<<endl;

	//}  
	//t2.InOrder();
	//cout<<"IsBalance: "<<t2.IsBalance()<<endl;

}
int main()
{
	Test();
	return 0;
}