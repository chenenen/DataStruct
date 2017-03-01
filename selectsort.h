#include<iostream>
using namespace std; 
//void SelectSort(int*a,int n)
//{
//	int i = 0;
//	for(i = 0; i<n; i++)
//	{
//		int min = i;
//		for(int j = i+1; j<n; j++)
//		{
//			if(a[min] > a[j])
//				min = j;
//		}
//		std::swap(a[min],a[i]);
//	}
//}


//”≈ªØ
void SelectSort(int* a, int n)
{
	int left = 0;
	int right = n-1;
	while(left <= right)
	{
		int min = left;
		int max = right;
		for(int i = left; i<=right; i++)
		{
			if(a[i] <= a[min])
				min = i;
			if(a[i] >= a[max])
				max = i;
			
		}
		std::swap(a[max],a[right]);
		if(min == right)
			min = max;
		std::swap(a[min],a[left]);
		left++;
		right--;
		
	}
}
void TestSelectSort()
{
	int i = 0;
	int a[10] = {1,2,4,5,6,8,9,0,7,3};
	SelectSort(a,10);
	for(int i = 0; i<10; i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}
