#include<iostream>
#include<assert.h>
using namespace std;
enum Type
{
	LINK, //无需搜索的节点类型
	THREDA,//已经被搜索过的节点类型
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
//迭代器的定义
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
	//重载!= 和 ==
	bool operator==(const Self& s)
	{
		return _node == s._node;
	}
	bool operator!=(const Self& s)
	{
		return _node != s._node;
	}
	//重载->和*
	Ref operator*()
	{
		return _node->_data;
	}
	Ptr operator->()
	{
		return &(_node->_data);
	}

	//重载前置++和后置++
	Self& operator++()
	{
		//首先此节点的右是否被搜索过，已经被搜索过了，直接跳
		if(_node->_righttag == THREDA)
			_node = _node->_right;
		//然后如果此节点没有被搜索过，那么先找它的右孩子，
		//然后看右孩子是否被线索过
		else
		{
			_node = _node->_right;
			while(_node->_lefttag == LINK)  //注意用while为了防止连跳
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
	//重载前置--和后置--
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
	//构造函数
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
	
	//中序遍历
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
	//中序打印
	void InOrderThdPrint()
	{
		_InOrderThdPrint(_root);
	}
	void _InOrderThdPrint(Node* root)
	{
		Node* cur = root;
		while(cur)
		{
			//先遍历左子树
			while(cur->_lefttag == LINK)
			{
				cur = cur->_left;
			}
			//找到终结的左节点，此时可以打印此节点的数据
			cout<<cur->_data<<" ";
			//判断节点的右是否被搜索过，如果被搜索过，就打印
			while(cur->_righttag == THREDA)
			{
				cur = cur->_right;
				if(cur)
					cout<<cur->_data<<" ";
			}
			//开始遍历右子树
			cur = cur->_right;
		}
		cout<<endl;
	}
	//构建搜索二叉树
	void InOrderThdding()
	{
		Node* pPre = NULL;
		_InOrderThdding(_root,pPre);
	}
	void _InOrderThdding(Node* root, Node*& pPre)//注意传的是引用
	{
		if(root == NULL)
			return ;
		Node* cur = root;
		//先遍历左子树
		_InOrderThdding(cur->_left,pPre);
		//1、找到左子树中左节点为空了
		if(cur->_left == NULL)
		{
			cur->_left = pPre;   //将此节点的左孩子给pPre
			cur->_lefttag = THREDA; //更改左的标志位
		}
		//3、用来找寻下一个链接点
		if(pPre != NULL && pPre->_right == NULL)
		{
			pPre->_right = cur;
			pPre->_righttag = THREDA;
		}
		//2、将当前的节点给pPre,用来找寻下一个链接的节点
		pPre = cur;
		//遍历完左子树后，再来遍历右子树
		_InOrderThdding(cur->_right,pPre);
	}
	//开始
	Iterator Begin()
	{
		Node* cur = _root;
		if(cur == NULL)
			return NULL;
		while(cur->_lefttag == LINK)
			cur = cur->_left;
		return cur;
	}
	//结束
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
