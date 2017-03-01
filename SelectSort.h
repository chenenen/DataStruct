#include<iostream>
using namespace std; 
//÷±Ω”≤Â»Î≈≈–Ú
void Sort(int* a,int n)
{
	/*int i = 0;
	for(i = 1; i<n; i++)
	{
		int temp = a[i];
		int end = i-1;
		while(end >= 0)
		{
			if(a[end] < temp)
			{
				a[end+1] = a[end];
				end--;
			}
			else
			{
				break;
			}
		}
		a[end+1] = temp;

	}*/
	for(int i = 1; i<n; i++)
	{
		int low = 0;
		int key = a[i];
		int high = i-1;
		while(low <= high)
		{
			int mid = low-((high-low)>>1);
			if(a[mid] > key)
				high = mid-1;
			else
				left = mid+1;
		}
		int end = i-1;
		while(end >= 0)
		{
			if(a[end] > key)
			{
				a[end+1]  = a[end];
				end--;
			}
			else
			{
				break;
			}
		}
		a[end+1] = temp;
}

////œ£∂˚≈≈–Ú
//void Sort(int* a, int n)
//{
//	int i = 0;
//	int gap = n;
//	int end = 0;
//	while(gap>1)
//	{
//		gap = gap/3+1;
//		for(i = gap; i<n; i++)
//		{
//			int temp = a[i];
//			end = i-gap;
//			while(end >= 0)
//			{
//				if(a[end] < temp)
//				{
//					a[end + gap] = a[end];
//					end -= gap;
//				}
//				else
//				{
//					break;
//				}
//
//			}
//			a[end+gap] = temp;
//		}
//	}
//}
void Test()
{
	int i = 0;
	int a[10] = {1,2,3,4,5,6,7,8,9,0};
	Sort(a,10);
	for(int i =0; i<10; i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;

}