#include<iostream>
#include<assert.h>
using namespace std;
template<typename T>
struct QueueNode
{
	QueueNode(const T& x)
		:_data(x)
		,_pNext(NULL)
	{}
	T _data;
	QueueNode<T>* _pNext;
};
template<typename T>
class Queue
{
	
public:
	typedef QueueNode<T> Node;
	Queue()
		:pHead(NULL)
		,pTail(NULL)
		,_size(0)
	{}
	Queue(const Queue<T>&q)
		:_pHead(NULL)
		,_pTail(NULL)
		,_size(q._size)
	{
		Node<T>* pRet = q.pHead;
		while(pRet)
		{
			Push(pRet->_data);
			pRet = pRet->_pNext;
		}
	}
	~Queue()
	{
		Node* pCur = pHead;
		while(pCur)
		{
			Node* pDel = pCur;
			pCur = pCur->_pNext;
			delete pDel;	
		}
	}
public:
	void Push(const T& x)//注意是队尾
	{
		Node* ptemp = new Node(x);
		if(pHead == NULL)
		{
			pHead = pTail = ptemp;
		}
		else
		{
			pTail->_pNext = ptemp;
			pTail = pTail->_pNext;
			pTail->_pNext = NULL;
		}
		++_size;
	}
	void Pop()//注意是队头
	{
		if(pHead == NULL)
		{
			return;
		}
		else if(pHead->_pNext == NULL)
		{
			delete pHead;
			pHead = NULL;
		}
		else
		{
			Node* pDel = pHead;
			pHead = pHead->_pNext;
			delete pDel;
		}
		--_size;
	}
	T& Front()
	{
		assert(pHead);
		return pHead->_data;
	}
	const T& Front()const
	{
		assert(pHead);
		return pHead->_data;
	}
	
	T& Back()
	{
		assert(pTail);
		return pTail->_data;
	}

	const T& Back()const
	{
		assert(pTail);
		return pTail->_data;
	}
	size_t Size()
	{
		size_t count = 0;
		Node* pCur = pHead;
		while(pCur)
		{
			count++;
			pCur = pCur->_pNext;
		}
		return count;
	}
	bool Empty()
	{
		return _size==0;
	}
protected:
	Node* pHead;
	Node* pTail;
	size_t _size;
};
//尾删尾插头插的测试
void Funtest()
{
	Queue<int> q;
	q.Push(1);
	q.Push(2);
	q.Push(3);
	q.Push(4);
	while(!q.Empty())
	{
		cout<<q.Front()<<" ";
		q.Pop();
	}
}
//其他函数的测试
void Funtest2()
{
	Queue<int> q;
	q.Push(1);
	q.Push(2);
	q.Push(3);
	q.Push(4);
	cout<<q.Back()<<endl;
	cout<<q.Size()<<endl;
	while(!q.Empty())
	{
	cout<<q.Front()<<" ";
		q.Pop();
	}
	
}

