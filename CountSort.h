#include<iostream>
using namespace std; 

void CountSort(int* a,int n)
{
	//1、首先确定要开一个多大的用于统计的数组
	int size = 0;
	int min = a[0];
	int max = a[0];
	for(int i = 0; i<n; i++)
	{
		if(a[i] < min)
			min = a[i];

		if(a[i] > max)
			max = a[i];
	}
	size = max-min+1;

	//2、开始进行统计原数组中对应下标出现的数
	int* count = new int[size];
	memset(count,0,sizeof(int)*size);
	for(int i = 0; i<n; i++)
	{
		count[a[i]-min]++;
	}

	//3、遍历哈希表，将count数组中大于0的数对应出原数组的值，
	//写入原数组中
	int j = 0;
	for(int i = 0; i<size; i++)
	{
		while(count[i]--)
		{
			a[j++] = i+min;
		}
	}
	delete[] count;

}

//测试函数
void TestCountSort()
{
	int a[10] = {2,5,3,8,3,7,10,9,4,0};
	int sz = sizeof(a)/sizeof(a[0]);
	CountSort(a,sz);
	for(int i = 0; i<sz; i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
} 
