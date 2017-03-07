#include<iostream>
using namespace std; 

void CountSort(int* a,int n)
{
	//1������ȷ��Ҫ��һ����������ͳ�Ƶ�����
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

	//2����ʼ����ͳ��ԭ�����ж�Ӧ�±���ֵ���
	int* count = new int[size];
	memset(count,0,sizeof(int)*size);
	for(int i = 0; i<n; i++)
	{
		count[a[i]-min]++;
	}

	//3��������ϣ����count�����д���0������Ӧ��ԭ�����ֵ��
	//д��ԭ������
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

//���Ժ���
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
