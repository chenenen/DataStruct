#ifndef __SearchBinaryTree__
#define __SearchBinaryTree__
#include<iostream>
#include<assert.h>
using namespace std;

//节点的定义
template<class K>
struct SearchBinaryTreeNode
{
	K _key;  //键值
	SearchBinaryTreeNode<K>* _left;
	SearchBinaryTreeNode<K>* _right;
	SearchBinaryTreeNode(const K& key)
		:_left(NULL)
		,_right(NULL)
		,_key(key)
	{}
};

template<class K>
class SearchBinaryTree
{
public:
	typedef SearchBinaryTreeNode<K> Node;
public:
	//构造函数
	//1、构造一个无参
	SearchBinaryTree()
		:_root(NULL)
	{}
	//2、用数组来进行构造
	SearchBinaryTree(K a[],int n)
	{
		for(int i = 0; i<n ;i++)
		{
			Insert(a[i]);	
		}
	}
	//查找函数(时间复杂度是O(n))
	Node* Find(const K& x)
	{
		if(_root == NULL)
			return NULL;
		Node* cur = _root;
		while(cur)
		{
			//如果要查找的数是比当前节点大的，那么就在右半边找
			if(cur->_key < x)
			{
				cur = cur->_right;
			}
			//如果要查找的数是比当前节点大的，那么就在左半边找
			else if(cur->_key >x)
			{
				cur = cur->_left;
			}
			//此处表明找到了
			else
			{
				return cur;
			}
		}
		//表明没找到
		return NULL;
	}
	//插入函数
	bool Insert(const K& x)
	{
		if(_root == NULL)
		{
			_root = new Node(x);
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;   //用于记录要插入点的前一个节点
		while(cur)
		{
			if(cur->_key <x)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if(cur->_key >x)
			{
				parent = cur;
				cur = cur->_left;
			}
			//如果要插入的值在搜索树中已经存在了，那么就无法插入
			else
			{
				return false;
			}
		}
		if(parent->_key <x)
		{
			parent->_right = new Node(x);
		}
		else
		{
			parent->_left = new Node(x);
		}
		return true;
	}
	//删除函数
	bool Remove(const K& x)
	{
		//分两种情况：
		//1、要删除的节点左或者右不为空时候（包括了如果删除的是叶子节点）
		//2、要删除的节点左右都为空的时候
		assert(_root);
		Node* cur = _root;
		//要考虑删除根节点的情况，所以这里将parent = NULL
		//Node* parent = cur;
		Node* parent = NULL;
		Node* del = NULL;//记录要删除的节点
		//先找到要删除的节点
		while(cur)
		{
			if(cur->_key < x)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if(cur->_key >x)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
			    //return false;
				break;
			}
		}
		if(cur == NULL)
			return false;
		//说明：根节点在第一次删除的时候可以，但是在如果它进了这
		//两个循环，就会出现问题，找不到parent
		//如果要删除的节点的左子树为空的话，
		if(cur->_left == NULL)
		{
			del = cur;
			if(parent == NULL)
			{
				_root = cur->_right;
			}
			else if(parent->_right == cur)
			{
				parent->_right = cur->_right ;
			}
			else
			{
				parent->_left = cur->_right;
			}
		}
		//如果要删除的节点的左子树为空的话
		else if(cur->_right == NULL)
		{
			del = cur;
			if(parent == NULL)
			{
				_root = cur->_left;
			}
			else if(parent->_right == cur)
			{
				parent->_right = cur->_left;
			}
			else
			{
				parent->_left = cur->_left;
			}
		}
		//如果被删除的节点的左右都为空的话，要用到的方法就是替换法
		//根据搜索二叉树的特点可知：
		//左子树的最右（即为最大值）
		//左子树的最左（即为最小值）
		else
		{ 
			//此处找的是右子树的最左节点，进行替换删除
			parent = cur;
			Node* sleft = cur->_right;
			while(sleft->_left)
			{
				parent = sleft;
				sleft = sleft->_left;
			}
			cur->_key = sleft->_key;
			if(parent->_left == sleft)
				parent->_left = sleft->_right;
			else
				parent->_right = sleft->_right;

			del = sleft;
		}
		delete del;
		del = NULL;
		return true;
	}
	//中序遍历
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
	void _InOrder(Node* root)
	{
		if(root == NULL)
			return;
		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}
	//析构函数
	~SearchBinaryTree()
	{
		Destory(_root);
		_root = NULL;
	}
	void Destory(Node* root)
	{
		if(root == NULL)
			return;
		Destory(root->_left);
		Destory(root->_right);
	}
	/*void Destory(Node*& root)
	{
		if(root == NULL)
			return;
		Destory(root->_left);
		Destory(root->_right);
		_root = NULL;

	}*/
	/*****************************非递归转递归*******************/
	//找关键值
Node* FindR(const K& key)
{
	_FindR(_root,key);
}
Node* _FindR(Node* root,const K& key)
{
	if(root == NULL)
		return NULL;

	if(root->_key > key)
		_FindR(root->_left,key);

	else if(root->_key <key)
		_FindR(root->_right,key);

	else
		return root;
}
//插入函数
bool InsertR(const K& key)
{
	return _InsertR(_root,key);
}
bool _InsertR(Node*& root,const K& key)
{
	if(root == NULL)
	{
		root = new Node(key);
		return true;
	}
	if(root->_key < key)
		_InsertR(root->_right,key);
	else if(root->_key > key)
		_InsertR(root->_left,key);
	else
	{
		return false;
	}

}
//删除函数
bool RemoveR(const K& key)
{
	return _RemoveR(_root,key);
}
bool _RemoveR(Node* &root,const K& key)
{
	Node* del = NULL;
	if(root == NULL)
		return false;
	if(root->_key > key)
		_RemoveR(root->_left,key);
	else if(root->_key < key)
		_RemoveR(root->_right,key);
	else
	{
		del = root;
		if(root->_left == NULL)
		{
			root = root->_right;
		}
		else if(root->_right == NULL)
		{
			root = root->_left;
		}
		else
		{
			Node* parent = root;
			Node* sleft = root->_right;
			//del = sleft;
			while(sleft->_left)
			{
				parent = sleft;
				sleft = sleft->_left;
			}
			root->_key = sleft->_key;
			if(parent->_left == sleft)
				parent->_left = sleft->_right;
			else
				parent->_right = sleft->_right;
			del = sleft;
		}
		delete del;
		del = NULL;
		return true;
	}
}
protected:
	Node* _root;
};

#endif
