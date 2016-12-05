#include<iostream>
#include<assert.h>
using namespace std;
template<typename T>
struct _ListNode
{
	T _data;
	_ListNode<T>* _pNext;
	_ListNode<T>* _pPre;
	_ListNode(const T& x)
		:_data(x)
		,_pNext(NULL)
		,_pPre(NULL)
	{}
};
template<typename T, typename Ref,typename Ptr>
struct _ListIterator
{
	typedef _ListNode<T> Node;
	typedef _ListIterator<T,T&,T*> Iterator;
	typedef _ListIterator<T,Ref,Ptr> Self;
	Node* _node;
	_ListIterator()
	{}
	_ListIterator(Node* node)
		:_node(node)
	{}
	bool operator != (const Self& s)
	{
		return _node != s._node;
	}
	bool operator == (const Self& s)
	{
		return _node == s._node;
	}
	//ǰ�üӼ�
	Self& operator++()
	{
		_node = _node->_pNext;
		return *this;
	}
	//���üӼ�
	Self operator++(int)
	{
		Self temp(*this);
		_node = _node->_pNext;
		return temp;
	}
	Ref operator*()
	{
		return _node->_data   //(*_node)._data;
	}
	Ptr operator->()
	{
		return &_node->_data;
	}
	//ǰ�ü���
	Self& operator--()
	{
		_node = _node->_pPre;
		return *this;
	}
	Self operator--(int)
	{
		Self temp(*this);
		_node = _node->_pPre;
		return temp;
	}
	
};
template<typename T>
class _List
{
	typedef _ListNode<T> Node;
public:
	typedef _ListIterator<T,T&,T*>  Iterator;
	typedef _ListIterator<T,const T&,const T*> ConstIterator;	
public:
	Node* BuyNode(const T& x)
	{
		return new Node(x);
	}
	_List()
		:_pHead(BuyNode(T()))    //�������Դ�һ����ʱ����
	{
		_pHead->_pNext = _pHead;
		_pHead->_pPre  = _pHead;
	}
	//��������
	void Push(const T&x)
	{
		/*Node* pCur = BuyNode(x);
		Node* pTail = _pHead->_pNext;
		pTail->_pNext = pCur;
		pCur->_pPre = pTail;
		_pHead->_pNext = pCur;
		pCur->_pPre = _pHead;*/
		Insert(End(),x);
	}
	//ɾ������
	void Pop()
	{
		Erase(--End());
	}
	//ͷ��
	void PushFront(const T& x)
	{
		Insert(Begin(),x);
	}
	//ͷɾ
	void PopFront()
	{
		Erase(Begin());
	}
	//���ض�λ�ò���һ������
	template <typename InputIterator>
	void Insert(Iterator pos,InputIterator first, InputIterator last)
	{
		while(first != last)
		{
			Insert(pos,*first);
			++first;
		}
	}
	//���ض���λ�ò�������
	Iterator Insert(Iterator pos, const T& x)
	{
		assert(pos._node);
		Node* pCur = pos._node;
		Node* pPre = pos._node->_pPre;
		Node* temp = new Node(x);
		pPre->_pNext = temp;
		temp->_pPre = pPre;
		pCur->_pPre = temp;
		temp->_pNext = pCur;
		return temp;
	}
	//ɾ���ض�λ�õ�����
	Iterator Erase(Iterator pos)
	{
		assert(pos._node && pos._node != _head);   //�жϴ�λ���Ƿ�Ϸ����Ҵ�λ�ò�����ͷ�ڵ�
		Node* pCur = pos._node->_pNext;
		Node* pPre = pos._node->_pPre;
		pCur->_pPre = pPre;
		pPre->_pnext = pCur;
		delete pos._node;
		return Iterator(pCur);
	}
	//
	const Iterator Begin()const
	{
		return _pHead->_pNext;
	}
	const Iterator End()const
	{
		return _pHead;
	}
	Iterator Begin()
	{
		return _pHead->_pNext;
	}
	Iterator End()
	{
		return _pHead;
	}


protected:
	Node* _pHead;
};
		

/***********************���Ժ���************************/
//���Բ������ݺ�ɾ������
void  Test1()
{
	_List<int> l1;
	l1.Push(1);
	l1.Push(2);
	l1.Push(3);
	l1.Push(4);
	_List<int>::Iterator it1 = l1.Begin();
	while(it1 != l1.End())
	{
		cout<<*it1<<" ";
		++it1;
	}	
	cout<<endl;
}
//ͷ��ͷɾ
void Test2()
{
	_List<int> l1;
	l1.Push(1);
	l1.Push(2);
	l1.Push(3);
	l1.Push(4);
	l1.PushFront(5);
	_List<int>::Iterator it1 = l1.Begin();
	while(it1 != l1.End())
	{
		cout<<*it1<<" ";
		++it1;
	}
	cout<<endl;
}
//���ض���λ�ò�������
void Test3()
{
	_List<int> l1;
	l1.Push(1);
	l1.Push(2);
	l1.Push(3);
	l1.Push(4);
	
	_List<int>::Iterator it1 = l1.Begin();
	it1 = l1.Insert(it1,6);   //Insert�����з���ֵ�������õ���������

	while(it1 != l1.End())
	{
		cout<<*it1<<" ";
		++it1;
	}
	cout<<endl;
}
//���Բ���һ������
void Test4()
{
	_List<int> l1;
	l1.Push(1);
	l1.Push(2);
	l1.Push(3);
	l1.Push(4);
	
	_List<int> l2;
	l2.Push(12);
	l2.Push(22);
	l2.Push(32);
	l2.Push(42);
	
	_List<int>::Iterator it1 = l1.Begin();
	l1.Insert(it1,l2.Begin(),l2.End());
	it1 = l1.Begin();
	while(it1!= l1.End())
	{
		cout<<*it1<<" ";
		++it1;
	}
	cout<<endl;4		
}
