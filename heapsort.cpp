#include<iostream>
#include<vector>
using namespace std;
template<typename T>
class Heap
{
public:
	//���캯��
	Heap()
	{}
	//����
	Heap(T* a, size_t n)
		:_a(a,a+n)
	{
		/*_a.reserve(n);
		for(size_t i = 0; i<n; i++)
		{
			_a.push_back(a[i]);
		}*/
		for(int i = (_a.size()-2)/2; i>=0; i--)
		{
			_Adjustdown(i);
		}
	}
	//β��
	void Push(const T& x)
	{
		_a.push_back(x);
		_Adjustup(_a.size()-1);
	}
	//βɾ
	void Pop()
	{
		swap(_a[0],_a[_a.size()-1]);
		_a.pop_back();
		_Adjustdown(0);
	}
	//����
	void HeapSort()
	{
		//���򣬽����
		for(int i = (_a.size()-2)/2; i>=0; --i)
		{
			_Adjustdown(i);
		}
		int end = _a.size()-1;
		while(end>0)
		{
			swap(_a[0],_a[_a.size()-1]);
			_Adjustdown(end);
			--end;
		}
	}

	/*//����ǲ��Ƕ�
	 bool CheckIsHeap(int i)
	{
		int parent = i;
		int child = 2*i+1;
		if(child<_a.size())
		{
			if( _a[child]<_a[parent])
			{
				if(child+1 <_a.size())
				{
					 if(_a[child+1]<_a[parent])
						 return true;
				}
			}
			else
				return false;
		}
		
	}*/
protected:
	//���µ���
	void _Adjustdown(int root)
	{
		int parent = root;
		int child = parent*2+1;
		//�˴���������������
		//һ���ǵ����ӵ�ֵС�ڸ�ĸ��ֵʱ������Ѿ���break�������
		//�ڶ����������ǵ���Ҷ�ӽڵ��ʱ��
		while(child<_a.size())
		{
			//�����Һ�����ֵ����
			if(child+1<_a.size() && _a[child+1]>_a[child])
			{
				++child;
			}
			//�����Ӻ͸�ĸ���Ƚ�
			if(_a[child]>_a[parent])
			{
				swap(_a[child],_a[parent]);
				parent = child;
				child = parent*2+1;
			}
			else
			{
				break;
			}
		}
	}
	//���ϵ���
	void _Adjustup(int i)
	{
		int child = i;
		int parent = (i-1)/2;
		while(child >= 0)
		{
			if(_a[child] > _a[parent])
			{
				swap(_a[child],_a[parent]);
				child = parent;
				parent = (parent-1)/2;
			}
			else
			{
				break;
			}
		}
	}
protected:
	vector<T> _a;
};

int main()
{
	int a [] = {10,16, 18, 12, 11, 13, 15, 17, 14, 19};
	Heap<int> hp1(a,sizeof(a)/sizeof(a[0]));
	hp1.Push(20);
	hp1.Pop();
	hp1.HeapSort();
	return 0;
}