#include<iostream>
#include<assert.h>
#include"TypeTraites.h"
using namespace std;
template<typename T>
class Vector
{
public:
	typedef T* Iterator;
	typedef const T* ConstIterator;
public:
	//构造函数
	Vector()
		:_start(0)
		,_finish(0)
		,_endofStorage(0)
	{}
	//拷贝构造函数
	Vector(const Vector<T>& v)
		:_start(new T[v.Size()])
	{
		if(TypeTraits<T>::IsPODType().Get())
		{
			memcpy(_start,v._start,sizeof(T)*v.Size());
		}
		else
		{
				for(size_t i = 0; i<v.Size(); i++)
			{
				_start[i] = v._start[i];
			}
		}
		_finish = _start+v.Size();
		_endofStorage = _start+v.Size();
	}
	//赋值运算符重载(简洁版)
	Vector& operator=(Vector<T> v)
	{
		std::swap(_start,v._start);
		std::swap(_finish,v._finish);
		std::swap(_endofStorage,v._endofStorage);
		return *this;
	}
	/*//赋值运算符重载（普通版）
	Vector& operator=(const Vector<T>& v)
	{
		//不建议采取这种，容易崩，举个例子如果先释放了2个，申请了10000个，程序就崩了
		if(this != &v)
		{
			Destory();
			_start = new T[v.Size()];
			_finish = _start+v.Size();
			_endofStorage = _start+v.Size();
				if(TypeTraits<T>::IsPODType().Get())
			{
				memcpy(_start,v._start,sizeof(T)*v.Size());
			}
			else
			{
					for(size_t i = 0; i<v.Size(); i++)
				{
					_start[i] = v._start[i];
				}
			}
		}
		return *this;
		//第二种方法：建议采取
		if(this != &v)
		{
			size_t size = Size();
			T* temp = new T[v.Size()];
			Destory();
				if(TypeTraits<T>::IsPODType().Get())
			{
				memcpy(temp,v._start,sizeof(T)*v.Size());
			}
			else
			{
					for(size_t i = 0; i<v.Size(); i++)
				{
					temp[i] = v._start[i];
				}
			}
			delete[]_start;
			_start = temp;
			_finish = _start+size;
			_endofStorage = _start+size;
		}
	}*/
	//销毁顺序表
	void Destory()
	{
		if(_start)
		{
			delete[] _start;
		}
		_start = _finish = _endofStorage = NULL;
	}
	//析构函数
	~Vector()
	{
		Destory();
	}
	//求顺序表的大小
	size_t Size()
	{
		return _finish-_start;
	}
	size_t Size()const
	{
		return _finish-_start;
	}
	//求顺序表的容量
	size_t Capacity()
	{
		return _endofStorage-_start;
	}
	size_t Capacity()const
	{
		return _endofStorage-_start;
	}
	//检查是否扩容
	void CheckCapacity()
	{
		size_t size = Size();
		size_t newcapacity = Capacity()*2+3;
		T* temp = new T[newcapacity];
		if(_finish == _endofStorage)
		{
			if(_start)
			{
				memcpy(temp,_start,sizeof(T)*(newcapacity));
			}
			delete[] _start; 
			_start = temp;
			_finish = _start+size;
			_endofStorage = _start+newcapacity;
		}
}
	//尾插
	void PushBack(const T&x)
	{
		CheckCapacity();
		*_finish = x;
		++_finish;
	}
	//尾删
	void PopBack()
	{
		assert(_start);
		--_finish;
	}
	
	Iterator Begin()
	{
		return _start;
	}
	const Iterator Begin()const
	{
		return _start;
	}
	Iterator End()
	{
		return _finish;
	}
	const Iterator End()const
	{
		return _finish;
	}
	//重载[]
	T& operator[](size_t pos)
	{
		assert(pos<Size());
		return _start[pos];
	}
	const T& operator[](size_t pos)const
	{
		assert(pos<Size());
		return _start[pos];
	}
	//在特定的位置插入元素
	void Insert(Iterator pos,const T&x)
	{
		CheckCapacity();
		//assert(pos<Size());
		assert(pos);
		Iterator pRet = _finish-1;
		while(pRet >= pos)
		{
			*(pRet+1) = *pRet;
			--pRet;
		}
		*pos = x;
		++_finish;
	}
	//在特定的位置删除元素
	void Erase(Iterator pos)
	{
		assert(pos);
		Iterator pDel = pos;
		while(pDel <_finish)
		{
			*pDel = *(pDel+1);
			++pDel;
		}
		--_finish;
	}
	//调整容器的大小
	void Resize(size_t sz, T c = T())
	{
		//如果要分配的大小小于原来的大小，直接截取
		if(sz < Size())
		{
			_finish -= Size()-sz;
		}
		//如果要分配的大小大于原来的大小

		//先要判断下分配之后的空间是否可够容纳
		//如果要分配的大小大于容量，则要重新开辟空间
		if(sz>Capacity())
		{
			Iterator pRet = _finish;
			size_t nsize = Size();
			size_t newcapacity = sz;
			Iterator temp = new T[newcapacity];
			//先将Size（）大小的空间值赋过去
			memcpy(temp,_start,sizeof(T)*nsize);
			delete[]_start;
			_start = temp;
			_finish = _start+sz;
			_endofStorage = _finish;
			//再将sz-Size()这段大小的用c填充
			while(pRet != _finish)
			{
				*pRet = c;
				++pRet;
			}
		}
		//如果分配的空间大小小于容量，则不用重新分配空间
		else
		{
			Iterator pRet = _finish;
			size_t nsize = Size();
			Iterator temp = new T[sz];
			memcpy(temp,_start,sizeof(T)*nsize);
			delete[]_start;
			_start = temp;
			_finish = _start+sz;
			while(pRet != _finish)
			{
				*pRet = c;
				++pRet;
			}
		}
	}
	//预分配N个空间
	void Reserve(size_t n)
	{
		size_t size = Size();
		size_t newcapacity = n;
		Iterator temp = new T[newcapacity];
		memcpy(temp,_start,sizeof(T)*Size());
		delete[]_start;
		_start = temp;
		_finish = _start+size;
		_endofStorage = _start+newcapacity;
	}
private:
	T* _start;
	T* _finish;
	T* _endofStorage;
};

/*********************测试函数*******************/
//测试尾插
void Test()
{
	Vector<int> v1;
	v1.PushBack(1);
	v1.PushBack(2);
	v1.PushBack(3);
	//v1.PushBack(4);
	Vector<int>::Iterator it1 = v1.Begin();
	while(it1 != v1.End())
	{
		cout<<*it1<<" ";
		++it1;
	}
	cout<<endl;
}
//尾删
void Test2()
{
	Vector<int> v1;
	v1.PushBack(1);
	v1.PushBack(2);
	v1.PushBack(3);
	v1.PushBack(4);
	
	v1.PopBack();
	v1.PopBack();
	v1.PopBack();
	Vector<int>::Iterator it2 = v1.Begin();
	while(it2 != v1.End())
	{
		cout<<*it2<<" ";
		++it2;
	}
	cout<<endl;
}
//测试在特定位置插入元素函数
void Test3()
{
	Vector<int> v1;
	v1.PushBack(1);
	v1.PushBack(2);
	v1.PushBack(3);
	v1.PushBack(4);
	Vector<int>::Iterator it1 = v1.Begin();
	v1.Insert(v1.Begin(),8);
	it1 = v1.Begin();
	while(it1 != v1.End())
	{
		cout<<*it1<<" ";
		++it1;
	}
	cout<<endl;
}
//在特定的位置删除元素
void Test4()
{
	Vector<int> v1;
	v1.PushBack(1);
	v1.PushBack(2);
	v1.PushBack(3);
	v1.PushBack(4);
	Vector<int>::Iterator it1 = v1.Begin();
	v1.Erase(v1.Begin());
	it1 = v1.Begin();
	while(it1 != v1.End())
	{
		cout<<*it1<<" ";
		++it1;
	}
	cout<<endl;
}

//测试重新调整空间大小
void Test5()
{
	Vector<int> v1;
	v1.PushBack(1);
	v1.PushBack(2);
	v1.PushBack(3);
	v1.PushBack(4);
	v1.Resize(8,7);
	cout<<v1.Size()<<endl;
}
//测试基本的函数：拷贝构造函数，赋值
void Test6()
{
	Vector<int> v1;
	Vector<int> v2(v1);
	Vector<int> v3;
	v3 = v1;
}

