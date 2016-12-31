#include<iostream>
#include<vector>
using namespace std;
template<typename T>
class Heap
{
public:
	//构造函数
	Heap()
	{}
	//建堆
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
	//尾插
	void Push(const T& x)
	{
		_a.push_back(x);
		_Adjustup(_a.size()-1);
	}
	//尾删
	void Pop()
	{
		swap(_a[0],_a[_a.size()-1]);
		_a.pop_back();
		_Adjustdown(0);
	}
	//堆排
	void HeapSort()
	{
		//升序，建大堆
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

	/*//检测是不是堆
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
	//向下调整
	void _Adjustdown(int root)
	{
		int parent = root;
		int child = parent*2+1;
		//此处的条件有两个：
		//一个是当孩子的值小于父母的值时候这个已经在break处理过了
		//第二个条件就是当是叶子节点的时候
		while(child<_a.size())
		{
			//找左右孩子中值最大的
			if(child+1<_a.size() && _a[child+1]>_a[child])
			{
				++child;
			}
			//将孩子和父母做比较
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
	//向上调整
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