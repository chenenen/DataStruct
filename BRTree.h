#include<iostream>
using namespace std; 
enum Color
{
	BLACK,
	RED,
};
template<class K,class V>
struct BRTreeNode
{
	K _key;
	V _value;
	Color _col;
	BRTreeNode<K,V>* _left;
	BRTreeNode<K,V>* _right;
	BRTreeNode<K,V>* _parent;
	BRTreeNode<K,V>(const K& key,const V& value)
		:_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_key(key)
		,_value(value)
		,_col(RED)
	{}
};
template<class K,class V>
class BRTree
{
	typedef BRTreeNode<K,V> Node;
public:
	BRTree()
		:_root(NULL)
	{}
	bool Insert(const K& key,const V& value)
	{
		Node* cur = _root;
		Node* parent = NULL;
		if(_root == NULL)
		{
			_root = new Node(key,value);
			_root->_col = BLACK;
			return true;
		}
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
		cur = new Node(key,value);
		if(parent->_key > key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		//到这里要进行分情况
		//五种情况
		//1、如果是空树那么就不用管或者是只有一个根节点，
		//   那么就将根节点的颜色设为黑色
		//2、如果父亲是黑色，插入一个红色，此种情况不用管
		//3、找u存在为红，只需变色
		//4、5、u不存在或者为黑，进行旋转
		while((parent) && (parent->_col == RED))
		{
			Node* grandfa = parent->_parent;
			if(grandfa->_left == parent)
			{
				Node* uncle = grandfa->_right;
				//只需变色
				if((uncle) && (uncle->_col == RED))
				{
					parent->_col = uncle->_col = BLACK;
					grandfa->_col = RED;
					cur = grandfa;
					parent = cur->_parent;
				}
				//进行旋转
				else
				{
					if(parent->_left == cur)
					{
						RotateR(grandfa);
						//swap(parent,cur);
						parent->_col = BLACK;
						grandfa->_col = RED;
					}
					else
					{
						RotateL(parent);
						RotateR(grandfa);
						cur->_col = BLACK;
						grandfa->_col = RED;
						break;
					}
				}
			}
			else
			{
				Node* uncle = grandfa->_left;
				if((uncle) && (uncle->_col == RED))
				{
					parent->_col = uncle->_col = BLACK;
					grandfa->_col = RED;
					cur = grandfa;
					parent = cur->_parent;
				}
				else
				{
					if(parent->_right == cur)
					{
						RotateL(grandfa);
						parent->_col = BLACK;
						grandfa->_col = RED;
						//swap(cur,parent);
					}
					else
					{
						RotateR(parent);
						RotateL(grandfa);
						cur->_col = BLACK;
						grandfa->_col = RED;
						break;
					}
				}
			}
		}
		_root->_col = BLACK;
		return true;
	}
	//中序打印
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

	//判断是否是红黑树
	//说明：1、检查树的颜色是否是正确的
	//		2、检查树中每一条路经的黑色节点个数是否是相同的

	bool IsBRTree()
	{	
		size_t k = 0;
		size_t num = 0;
		Node* cur = _root;
		if(_root == NULL)
			return true;
		if(_root && _root->_col == RED)
			return false;
		while(cur)
		{
			if(cur->_col == BLACK)
				k++;
			cur = cur->_left;
		}
		
		return CheckCol(_root) && CheckBlackNum(_root,k,num);
	}

	//检查颜色
	bool CheckCol(Node* root)
	{
		if(root == NULL)
			return true;
		if(root->_col == RED && root->_parent->_col == RED)
			return false;
		return CheckCol(root->_left)
			&& CheckCol(root->_right);
	}

	//检查每条路经中黑节点的个数
	bool CheckBlackNum(Node* root,const size_t k,size_t num)
	{
		if(root == NULL)
			return true;
		if(root->_col == BLACK)
			num++;
		if((root->_left == NULL) && (root->_right == NULL) 
			&& (k != num))
			return false;
		return CheckBlackNum(root->_left,k,num)
		      && CheckBlackNum(root->_right,k,num);

	}
	//左旋
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
		}
		else
		{
			if(ppNode->_left == parent)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;
		}
			subR->_parent = ppNode;
	}
	//右旋
	void RotateR(Node* parent)
	{
		Node* subL= parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if(subLR)
			subLR->_parent = parent;

		Node* ppNode = parent->_parent;
		subL->_right= parent;
		parent->_parent = subL;

		if(ppNode == NULL)
		{
			_root = subL;
		}
		else
		{
			if(ppNode->_left == parent)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;
		}
			subL->_parent = ppNode;		
	}
protected:
	Node* _root;
};
