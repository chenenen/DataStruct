#include<iostream>
#include<assert.h>
#include<math.h>
using namespace std;
template<class K,class V>
struct AVLTreeNode
{
	K _key;   //�ؼ���
	V _value;  //�ؼ�ֵ
	int _bf;   //ƽ������
	AVLTreeNode<K,V>* _left;
	AVLTreeNode<K,V>* _right;
	AVLTreeNode<K,V>* _parent;

	AVLTreeNode(const K& key,V& value)
		:_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_key(key)
		,_value(value)
		,_bf(0)
	{}
};

template<class K,class V>
class AVLTree
{
public:
	typedef AVLTreeNode<K,V> Node;
public:
	//���캯��
	AVLTree()
		:_root(NULL)
	{}
	//���Һ���
	Node* Find(const K& key)
	{
		if(_root == NULL)
			return NULL;
		Node* cur = _root;
		while(cur)
		{
			if(cur->_key > key)
			{
				cur = cur->_left;
			}
			else if(cur->_key < key)
			{
				cur = cur->_right;
			}
			else
			{
				return cur;
			}
		}
		return NULL;
	}
	//���뺯��
	bool Insert(const K& key,V& value)
	{
		if(_root == NULL)
		{
			_root = new Node(key,value);
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;
		//1������Ҫ����ĵ�
		while(cur)
		{
			if(cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if(cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}
		//2����ʱ����Ҫ�����ֵ
		cur = new Node(key,value);
		if(parent->_key > key)
		{
			parent->_left = cur;
			//parent = cur->_parent;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			//parent = cur->_parent;
			cur->_parent = parent;
		}
		//3������֮���Ҫ���е�������Ϊ����֮��֪�����Ƿ���AVL��
		//���ڵ��ƽ�����ӷ�����������º�
		//1��Ϊ0��˵��֮ǰ��1���������ϸ���
		//2��Ϊ1/-1��˵��֮ǰ��0�����ϸ���
		//3��Ϊ2/-2�������㣬������£�������ת
		while(parent)
		{
			if(parent->_left == cur)
			{
				parent->_bf -= 1;
			}
			else
			{
				parent->_bf += 1;
			}
			//��ʽ����ƽ�����ӵĵ���
			if(parent->_bf == 0)
			{
				break;
			}
			else if(parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = cur->_parent;
			}
			//������ת��ʱ����Ҫ���з����
			else if(parent->_bf == 2 || parent->_bf == -2)
			{
				//���������

				if(parent->_bf == 2)
				{
					//����
					if(cur->_bf == 1)
					{
						RotateL(parent);
					}

					//������
					//˵��������Ҫ�����������㲻ͬ��ƽ�����ӵĸı�Ͳ�ͬ

					else   //cur->bf == -1
					{
						RotateRL(parent);
					}
				}

				/*if(parent->_bf == -2)*/
				else
				{

					//�ҵ���
					if(cur->_bf == -1)
					{
						RotateR(parent);
					}

					//���ҵ���
					//˵����ͬ������㲻ͬ��ƽ�����ӵĸı�Ͳ�ͬ
					else
					{
						RotateLR(parent);
					}
				}
				break;
			}
			else
			{
				cout<<"ƽ�������쳣��"<<endl;
				assert(false);
			}
		}
		return true;//��ѭ������

	}

	//�ж�һ�Ŷ������Ƿ���AVL��
	//˼·���������ø߶ȿ�ƽ�������Ƿ���-1��0��1
	//�������ַ���ʱ�临�Ӷ���O��N*N��
	bool IsBalance()
	{
		return _IsBalance(_root);
	}
	bool _IsBalance(Node* root)
	{
		//���ǿ�����ʱ��Ҳ��AVL��
		if(root == NULL)
			return true;
		int leftdepth = _Depth(root->_left);
		int rightdepth = _Depth(root->_right);
		if((rightdepth-leftdepth) != root->_bf)
		{
			cout<<"ƽ�������쳣��"<<root->_key<<endl;
		}
		return abs(rightdepth-leftdepth)<=1
			&& _IsBalance(root->_left)
			&& _IsBalance(root->_right);
	}

	//�����Ż����ж��Ƿ���ƽ�������
	//˼·������ֻ����һ�Σ�ÿ�ν��еݹ��ȥ�ķ���ֵ
	//          �ǽ���һ�εĸ߶ȴ���
	//ʱ�临�Ӷ���O��N*N��
	bool IsBalanceOP()
	{
		size_t depth = 0;
		return _IsBalanceOP(_root,depth);
	}
	bool _IsBalanceOP(Node* root,size_t depth)
	{
		if(root == NULL)
		{
			depth = 0;
			return true;
		}
		size_t leftdepth = 0;
		size_t rightdepth = 0;
		//�Ƚ����жϴ˽ڵ�����������Ƿ���ƽ�������
		if(_IsBalanceOP(root->_left,leftdepth)
			&& _IsBalanceOP(root->_right,rightdepth))
		{
			//����ǵĻ�����ô�����������жϴ˽ڵ���ƽ�������
			//���ҽ����ҽڵ��и߶ȴ���
			depth = leftdepth > rightdepth? leftdepth+1:rightdepth+1;
			return abs(leftdepth-rightdepth) < 2;
		}
		return false;
		
	}

		//�������
	void InOrder()
	{
		 _InOrder(_root);
	}
	void _InOrder(Node* root)
	{
		if(root == NULL)
			return;
		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}
protected:
	//����
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if(subRL)
			subRL->_parent = parent;

		Node* ppNode = parent->_parent;
		subR->_left = parent;
		parent->_parent = subR;

		if(ppNode == NULL)
		{
			_root = subR;
			subR->_parent = NULL;
		}
		else
		{
			if(ppNode->_left == parent)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;
			subR->_parent = ppNode;
		}
		parent->_bf = subR->_bf = 0;
	}

	//�ҵ���
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if(subLR)
			subLR->_parent = parent;

		Node* ppNode = parent->_parent;
		subL->_right = parent;
		parent->_parent = subL;

		if(ppNode == NULL)
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else
		{
			if(ppNode->_left == parent)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;
			subL->_parent = ppNode;
		}
		parent->_bf = subL->_bf = 0;
	}

	/*//������ת
	void RotateLR(Node* parent)
	{
		Node* cur = parent->_left;
		RotateL(cur);
		RotateR(cur);
	}
	
	//������ת
	void RotateRL(Node* parent)
	{
		Node* cur = parent->_right;
		RotateR(cur);
		RotateL(cur);
	}*/
	/***************����ϸ�������˫��*****************/
	//������
	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(parent->_left);
		RotateR(parent);

		if(bf == 1)
		{
			subL->_bf = -1;
			parent->_bf = 0;
		}
		else if(bf == -1)
		{
			subL->_bf = 0;
			parent->_bf = 1;
		}
		else 
		{
			subL->_bf = parent->_bf = 0;
		}
		subLR->_bf = 0;
	}
	//������
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		RotateR(parent->_right);
		RotateL(parent);

		if(bf == 1)
		{
			subR->_bf = 0;
			parent->_bf = -1;
		}
		else if(bf == -1)
		{
			subR->_bf = 1;
			parent->_bf = 0;
		}
		else
		{
			subR->_bf = parent->_bf = 0;
		}
		subRL->_bf = 0;
	}
	//��ƽ��������ĸ߶�
	size_t Depth()
	{
		return _Depth(_root);
	}
	size_t _Depth(Node* &root)
	{
		if(root == NULL)
			return 0;
		size_t leftD = _Depth(root->_left);
		size_t rightD = _Depth(root->_right);
		return leftD>rightD ? leftD+1:rightD+1;
	}

protected:
	Node* _root;
};