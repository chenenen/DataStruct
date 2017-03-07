#include<iostream>
using namespace std; 
//给一个数，求这个数有多少位
int GetDigit(int* a,size_t n)
{
	int base = 10;
	int digit = 1;
	int num = 0;
	for(int i = 0; i<n; i++)
	{
		while(a[i] >= base)
		{
			digit++;
			base *= 10;
		}
	}

	return digit;
}
void LSDdigit(int* a,int n)
{
	int digit = GetDigit(a,n);  //得到位数
	int count[10] = {0};
	int start[10] = {0};
	int base = 1;
	 //开辟一个新的数组，用于存放一次排序后的数
	int*temp = new int[n];      
	while(digit--)
	{
		//首先按各位进行统计个位上的数出现的次数
		for(int i = 0; i<n; i++)
		{
			int num = (a[i]/base)%10;
			count[num]++;

		}
		start[0] = 0;
		for(int i = 1; i<10; i++)
		{
			start[i] = start[i-1]+count[i-1];
		}
		for(int i = 0; i<10; i++)
		{
			int num = (a[i]/base)%10;
			temp[start[num]++] = a[i];
			count[num]--;
		}
		for(int i = 0; i<10; i++)
		{
			a[i] = temp[i];
		}
		base *= 10;
	}
	delete[] temp;	
	
}

//测试函数
void TestLSDdigit()
{
	int a[10] = {73,22,93,43,55,14,28,65,39,81};
	int sz = sizeof(a)/sizeof(a[0]);
	LSDdigit(a,sz);
	for(int i = 0; i<sz; i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}