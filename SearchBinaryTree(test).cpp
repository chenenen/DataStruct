#include"SearchBinaryTree.h"
int main()
{
	int a[10] = {5,3,4,1,7,8,2,6,0,9};
	SearchBinaryTree<int> bst1;
	for(int i = 0; i<sizeof(a)/sizeof(a[0]); i++)
	{
		bst1.Insert(a[i]);
	}

	bst1.InOrder();
	//²âÊÔ²åÈë
	bst1.Insert(10);
	bst1.Insert(5);
	bst1.Insert(12);
	bst1.InOrder();
	//²âÊÔÉ¾³ý
	bst1.Remove(0);
	bst1.Remove(8);
	bst1.Remove(7);

	bst1.InOrder();

	bst1.Remove(3);
	bst1.Remove(5);
	bst1.InOrder();

	//²âÊÔ×îºóÉ¾³ý¸ù½Úµã
	bst1.Remove(0);
	bst1.Remove(1);
	bst1.Remove(2);
	bst1.Remove(3);
	bst1.Remove(4);
	bst1.Remove(6);
	bst1.Remove(7);
	bst1.Remove(8);
	bst1.Remove(9);
	bst1.Remove(5);
	bst1.InOrder();

	return 0;
}