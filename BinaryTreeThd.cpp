#include<iostream>
#include<assert.h>
using namespace std;
enum Type
{
	LINK, //���������Ľڵ�����
	THREDA,//�Ѿ����������Ľڵ�����
};
template<class T>
struct BinaryTreeThdNode
{
	T _data;
	BinaryTreeThdNode<T>* _left;
	BinaryTreeThdNode<T>* _right;
	Type _lefttag;
	Type _righttag;
	BinaryTreeThdNode(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
		,_lefttag(LINK)
		,_righttag(LINK)
	{}
};
//�������Ķ���
template<typename T, typename Ref,typename Ptr>
struct BinaryTreeThdIterator
{
	typedef BinaryTreeThdNode<T> Node;
	//typedef BinatyTreeThdItetator<T,T&,T*> Iterator;
	typedef BinaryTreeThdIterator<T,T&,T*> Self;
	Node* _node;
	BinaryTreeThdIterator(Node* Node = NULL)
		:_node(Node)
	{}
	//����!= �� ==
	bool operator==(const Self& s)
	{
		return _node == s._node;
	}
	bool operator!=(const Self& s)
	{
		return _node != s._node;
	}
	//����->��*
	Ref operator*()
	{
		return _node->_data;
	}
	Ptr operator->()
	{
		return &(_node->_data);
	}

	//����ǰ��++�ͺ���++
	Self& operator++()
	{
		//���ȴ˽ڵ�����Ƿ����������Ѿ����������ˣ�ֱ����
		if(_node->_righttag == THREDA)
			_node = _node->_right;
		//Ȼ������˽ڵ�û�б�����������ô���������Һ��ӣ�
		//Ȼ���Һ����Ƿ�������
		else
		{
			_node = _node->_right;
			while(_node->_lefttag == LINK)  //ע����whileΪ�˷�ֹ����
				_node = _node->_left;
		}
		return *this;
	}
	Self operator++(int)
	{
		Self temp(*this);
		++(*this);
		return temp;
	}
	//����ǰ��--�ͺ���--
	Self& operator--()
	{
		if(_node->_lefttag == THREDA)
			_node = _node->_left;
		else
		{
			_node = _node->_left;
			while(_node->_right == LINK)
				_node = _node->_right;
		}
		return *this;
	}
	Self operator--(int)
	{
		Self temp(*this);
		--(*this);
		return temp;
	}

};
template<class T>
class BinaryTreeThd
{
public:
	typedef BinaryTreeThdNode<T> Node;
	typedef BinaryTreeThdIterator<T,T&,T*> Iterator;
	typedef BinaryTreeThdIterator<T,const T&,const T*> ConstIterator; 
public:
	//���캯��
	BinaryTreeThd(T* a, size_t size,const T& invalue = 0)
	{
		assert(a);
		size_t index = 0;
		_root = CreateTree(a,size,index,invalue);
	}
	Node* CreateTree(T* a,size_t size,size_t & index,const T& invalue = 0)
	{
		//Node* root = NULL;
		if(index<size && a[index] != invalue)
		{
			Node* newroot = new Node(a[index]);
			newroot->_left = CreateTree(a,size,++index,invalue);
			newroot->_right= CreateTree(a,size,++index,invalue);
			return newroot;
		}
		return NULL;
	}
	
	//�������
	void InOrdedThd()
	{
		_InOrderThd(_root);
		cout<<endl;
	}
	void _InOrderThd(Node* root)
	{
		if(root == NULL)
			return;
		if(root->_lefttag == LINK)
		_InOrderThd(root->_left);
		cout<<root->_data<<" ";
		if(root->_righttag == LINK)
		_InOrderThd(root->_right);
	}
	//�����ӡ
	void InOrderThdPrint()
	{
		_InOrderThdPrint(_root);
	}
	void _InOrderThdPrint(Node* root)
	{
		Node* cur = root;
		while(cur)
		{
			//�ȱ���������
			while(cur->_lefttag == LINK)
			{
				cur = cur->_left;
			}
			//�ҵ��ս����ڵ㣬��ʱ���Դ�ӡ�˽ڵ������
			cout<<cur->_data<<" ";
			//�жϽڵ�����Ƿ�����������������������ʹ�ӡ
			while(cur->_righttag == THREDA)
			{
				cur = cur->_right;
				if(cur)
					cout<<cur->_data<<" ";
			}
			//��ʼ����������
			cur = cur->_right;
		}
		cout<<endl;
	}
	//��������������
	void InOrderThdding()
	{
		Node* pPre = NULL;
		_InOrderThdding(_root,pPre);
	}
	void _InOrderThdding(Node* root, Node*& pPre)//ע�⴫��������
	{
		if(root == NULL)
			return ;
		Node* cur = root;
		//�ȱ���������
		_InOrderThdding(cur->_left,pPre);
		//1���ҵ�����������ڵ�Ϊ����
		if(cur->_left == NULL)
		{
			cur->_left = pPre;   //���˽ڵ�����Ӹ�pPre
			cur->_lefttag = THREDA; //������ı�־λ
		}
		//3��������Ѱ��һ�����ӵ�
		if(pPre != NULL && pPre->_right == NULL)
		{
			pPre->_right = cur;
			pPre->_righttag = THREDA;
		}
		//2������ǰ�Ľڵ��pPre,������Ѱ��һ�����ӵĽڵ�
		pPre = cur;
		//����������������������������
		_InOrderThdding(cur->_right,pPre);
	}
	//��ʼ
	Iterator Begin()
	{
		Node* cur = _root;
		if(cur == NULL)
			return NULL;
		while(cur->_lefttag == LINK)
			cur = cur->_left;
		return cur;
	}
	//����
	Iterator End()
	{
		return NULL;
	}
private:
	Node* _root;
};
int main()
{
	int a[10] = {1,2,3,'#','#',4,'#','#',5,6};
	BinaryTreeThd<int> t1(a,sizeof(a)/sizeof(a[0]),'#');
	t1.InOrderThdding();
	t1.InOrderThdPrint();
	BinaryTreeThd<int>::Iterator it1 = t1.Begin();
	while(it1 != t1.End())
	{
		cout<<*it1<<" ";
		++it1;
	}
	cout<<endl;
	BinaryTreeThd<int>::Iterator it1 = t1.
}
