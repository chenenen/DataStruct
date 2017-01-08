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

protected:
	Node* _root;
};

#endif
