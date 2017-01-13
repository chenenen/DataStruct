#ifndef __SearchBinaryTree__
#define __SearchBinaryTree__
#include<iostream>
#include<assert.h>
using namespace std;

//�ڵ�Ķ���
template<class K>
struct SearchBinaryTreeNode
{
	K _key;  //��ֵ
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
	//���캯��
	//1������һ���޲�
	SearchBinaryTree()
		:_root(NULL)
	{}
	//2�������������й���
	SearchBinaryTree(K a[],int n)
	{
		for(int i = 0; i<n ;i++)
		{
			Insert(a[i]);	
		}
	}
	//���Һ���(ʱ�临�Ӷ���O(n))
	Node* Find(const K& x)
	{
		if(_root == NULL)
			return NULL;
		Node* cur = _root;
		while(cur)
		{
			//���Ҫ���ҵ����Ǳȵ�ǰ�ڵ��ģ���ô�����Ұ����
			if(cur->_key < x)
			{
				cur = cur->_right;
			}
			//���Ҫ���ҵ����Ǳȵ�ǰ�ڵ��ģ���ô����������
			else if(cur->_key >x)
			{
				cur = cur->_left;
			}
			//�˴������ҵ���
			else
			{
				return cur;
			}
		}
		//����û�ҵ�
		return NULL;
	}
	//���뺯��
	bool Insert(const K& x)
	{
		if(_root == NULL)
		{
			_root = new Node(x);
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;   //���ڼ�¼Ҫ������ǰһ���ڵ�
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
			//���Ҫ�����ֵ�����������Ѿ������ˣ���ô���޷�����
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
	//ɾ������
	bool Remove(const K& x)
	{
		//�����������
		//1��Ҫɾ���Ľڵ�������Ҳ�Ϊ��ʱ�򣨰��������ɾ������Ҷ�ӽڵ㣩
		//2��Ҫɾ���Ľڵ����Ҷ�Ϊ�յ�ʱ��
		assert(_root);
		Node* cur = _root;
		//Ҫ����ɾ�����ڵ��������������ｫparent = NULL
		//Node* parent = cur;
		Node* parent = NULL;
		Node* del = NULL;//��¼Ҫɾ���Ľڵ�
		//���ҵ�Ҫɾ���Ľڵ�
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
		//˵�������ڵ��ڵ�һ��ɾ����ʱ����ԣ������������������
		//����ѭ�����ͻ�������⣬�Ҳ���parent
		//���Ҫɾ���Ľڵ��������Ϊ�յĻ���
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
		//���Ҫɾ���Ľڵ��������Ϊ�յĻ�
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
		//�����ɾ���Ľڵ�����Ҷ�Ϊ�յĻ���Ҫ�õ��ķ��������滻��
		//�����������������ص��֪��
		//�����������ң���Ϊ���ֵ��
		//�����������󣨼�Ϊ��Сֵ��
		else
		{ 
			//�˴��ҵ���������������ڵ㣬�����滻ɾ��
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
	//�������
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
	//��������
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
	/*****************************�ǵݹ�ת�ݹ�*******************/
	//�ҹؼ�ֵ
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
//���뺯��
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
//ɾ������
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
