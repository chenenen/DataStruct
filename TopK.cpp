/*����˵������N�����ݣ�������ǰk��*/
#include<iostream>
using namespace std;

void _Adjustdown(int* a,int n,int root)
{
	int parent = root;
	int child = 2*parent+1;
	while(child < n)
	{
		if(child+1<n && a[child+1]<a[child])
		{
			++child;
		}
		if(a[child]<a[parent])
		{
			swap(a[child],a[parent]);
			parent = child;
			child = parent*2+1;
		}
		else
		{
			break;
		}
	}
}

void TopK(int* a,int n,int k)
{
	//�Ƚ�һ��k��С�Ķ�
	int* _heap = new int[k];
	//��С��
	for(size_t i =0;i<k;i++)
	{
		_heap[i] = a[i];
	}

	for(int i = (k-2)/2; i>=0; --i)
	{
		_Adjustdown(_heap,k,i);
	}
	//��������Ԫ�غͺ����Ԫ�ؽ��бȽϣ������
	//������Ԫ�ش�ֱ�Ӹ�ֵ��Ȼ�����µ���
	for(int i = k; i<n; i++)
	{
		if(a[i]>_heap[0])
		{	
			_heap[0] = a[i];
			_Adjustdown(_heap,k,0);
		}
	}
	for(int i = 0; i<k; i++)
	{
		cout<<_heap[i]<<" ";
	}
	cout<<endl;
	delete[]_heap;
}

int main()
{
	const int N = 100000;
	int k = 10;
	int a[N];
	for(size_t i = 0;i<N;++i)
	{
		a[i] = rand()%1000;
	}

	a[5] = 1001;
	a[10] = 1005;
	a[99] = 1010;
	a[100] = 1100;
	a[111] = 1102;

	TopK(a,N,k);


	return 0;
}