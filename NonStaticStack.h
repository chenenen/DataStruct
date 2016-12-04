/*
* author:chenenen
* date:2016/12/4
*/

#include<iostream>
#include<assert.h>
using namespace std;

//动态栈

template<typename T>
class Stack
{
public:
	Stack()
		:arr(NULL)
		,_size(0)
		,_capacity(0)
	{}
	Stack(const Stack<T>& s)
		:arr(NULL)
		,_size(s._size)
		,_capacity(s._capacity)
	{
		arr = new int[s._capacity];
		for(size_t i = 0; i<s._size; i++)
		{
			arr[i] = s.arr[i];
		}
	}
	Stack<T>& operator=(const Stack<T>&s)
	{
		if(this != &s)
		{
			_capacity = _capacity*2+3;
			T*temp = new int[s._capacity];
			for(size_t i = 0; i<s._size; i++)
			{
				temp[i] = s.arr[i];
			}
			delete[]arr;
			arr = temp;
			_size = s._size;
			_capacity = s._capacity;
		}
		return *this;
	}
	~Stack()
	{
		delete[]arr;
		_size = 0;
		_capacity = 0;
	}

public:
	void CheckCapacity()
	{
		if(_size>=_capacity)
		{
			T *temp = new int[_capacity*2+3];
			for(size_t i = 0; i<_size; i++)
				{
					temp[i] = arr[i];
				}
				delete[] arr;
			arr = temp;
			_capacity =  _capacity*2+3;
			
		}
	}
		
	void Push(const T& x)
	{
		CheckCapacity();
		arr[_size] = x;
		++_size;
	}
	void Pop()
	{
		assert(arr);
		--_size;
	}
	T& Top()
	{
		return arr[_size-1];
	}
	const T& Top()const
	{
		return arr[_size-1];
	}
	size_t Size()
	{
		return _size;
	}
	bool Empty()
	{
		return _size==0;
	}

protected:
    T*arr;
	size_t _size;
	size_t _capacity;
};
//测试基本函数
void Funtest1()
{
	Stack<int> s1;
	Stack<int> s2(s1);
	Stack<int> s3;
	s3 = s2;
}
//测试插入删除函数
void Funtest2()
{
	Stack<int> s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	while(!s.Empty())
	{
		cout<<s.Top()<<" ";
		s.Pop();
	}	
}
//测试后面的函数
void Funtest3()
{
	Stack<int> s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Size();
	
}