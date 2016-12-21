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
	//���캯��
	Vector()
		:_start(0)
		,_finish(0)
		,_endofStorage(0)
	{}
	//�������캯��
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
	//��ֵ���������(����)
	Vector& operator=(Vector<T> v)
	{
		std::swap(_start,v._start);
		std::swap(_finish,v._finish);
		std::swap(_endofStorage,v._endofStorage);
		return *this;
	}
	/*//��ֵ��������أ���ͨ�棩
	Vector& operator=(const Vector<T>& v)
	{
		//�������ȡ���֣����ױ����ٸ�����������ͷ���2����������10000��������ͱ���
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
		//�ڶ��ַ����������ȡ
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
	//����˳���
	void Destory()
	{
		if(_start)
		{
			delete[] _start;
		}
		_start = _finish = _endofStorage = NULL;
	}
	//��������
	~Vector()
	{
		Destory();
	}
	//��˳���Ĵ�С
	size_t Size()
	{
		return _finish-_start;
	}
	size_t Size()const
	{
		return _finish-_start;
	}
	//��˳��������
	size_t Capacity()
	{
		return _endofStorage-_start;
	}
	size_t Capacity()const
	{
		return _endofStorage-_start;
	}
	//����Ƿ�����
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
	//β��
	void PushBack(const T&x)
	{
		CheckCapacity();
		*_finish = x;
		++_finish;
	}
	//βɾ
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
	//����[]
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
	//���ض���λ�ò���Ԫ��
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
	//���ض���λ��ɾ��Ԫ��
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
	//���������Ĵ�С
	void Resize(size_t sz, T c = T())
	{
		//���Ҫ����Ĵ�СС��ԭ���Ĵ�С��ֱ�ӽ�ȡ
		if(sz < Size())
		{
			_finish -= Size()-sz;
		}
		//���Ҫ����Ĵ�С����ԭ���Ĵ�С

		//��Ҫ�ж��·���֮��Ŀռ��Ƿ�ɹ�����
		//���Ҫ����Ĵ�С������������Ҫ���¿��ٿռ�
		if(sz>Capacity())
		{
			Iterator pRet = _finish;
			size_t nsize = Size();
			size_t newcapacity = sz;
			Iterator temp = new T[newcapacity];
			//�Ƚ�Size������С�Ŀռ�ֵ����ȥ
			memcpy(temp,_start,sizeof(T)*nsize);
			delete[]_start;
			_start = temp;
			_finish = _start+sz;
			_endofStorage = _finish;
			//�ٽ�sz-Size()��δ�С����c���
			while(pRet != _finish)
			{
				*pRet = c;
				++pRet;
			}
		}
		//�������Ŀռ��СС���������������·���ռ�
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
	//Ԥ����N���ռ�
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

/*********************���Ժ���*******************/
//����β��
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
//βɾ
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
//�������ض�λ�ò���Ԫ�غ���
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
//���ض���λ��ɾ��Ԫ��
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

//�������µ����ռ��С
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
//���Ի����ĺ������������캯������ֵ
void Test6()
{
	Vector<int> v1;
	Vector<int> v2(v1);
	Vector<int> v3;
	v3 = v1;
}

