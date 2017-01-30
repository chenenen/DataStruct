#include<iostream>
#include<assert.h>
#include<math.h>
using namespace std;
template<class K,class V>
struct AVLTreeNode
{
	K _key;   //关键字
	V _value;  //关键值
	int _bf;   //平衡因子
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
	//构造函数
	AVLTree()
		:_root(NULL)
	{}
	//查找函数
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
	//插入函数
	bool Insert(const K& key,V& value)
	{
		if(_root == NULL)
		{
			_root = new Node(key,value);
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;
		//1、先找要插入的点
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
		//2、此时插入要插入的值
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
		//3、插入之后就要进行调整，因为插入之后不知道它是否还是AVL树
		//父节点的平衡因子分情况：（更新后）
		//1）为0，说明之前是1，无需向上更新
		//2）为1/-1，说明之前是0，往上更新
		//3）为2/-2，不满足，无需更新，进行旋转
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
			//正式进行平衡因子的调节
			if(parent->_bf == 0)
			{
				break;
			}
			else if(parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = cur->_parent;
			}
			//进行旋转的时候又要进行分情况
			else if(parent->_bf == 2 || parent->_bf == -2)
			{
				//四种情况：

				if(parent->_bf == 2)
				{
					//左单旋
					if(cur->_bf == 1)
					{
						RotateL(parent);
					}

					//右左单旋
					//说明：这里要分情况，插入点不同，平衡因子的改变就不同

					else   //cur->bf == -1
					{
						RotateRL(parent);
					}
				}

				/*if(parent->_bf == -2)*/
				else
				{

					//右单旋
					if(cur->_bf == -1)
					{
						RotateR(parent);
					}

					//左右单旋
					//说明：同理，插入点不同，平衡因子的改变就不同
					else
					{
						RotateLR(parent);
					}
				}
				break;
			}
			else
			{
				cout<<"平衡因子异常！"<<endl;
				assert(false);
			}
		}
		return true;//在循环外面

	}

	//判断一颗二叉树是否是AVL树
	//思路分析：利用高度看平衡因子是否是-1，0，1
	//采用这种方法时间复杂度是O（N*N）
	bool IsBalance()
	{
		return _IsBalance(_root);
	}
	bool _IsBalance(Node* root)
	{
		//当是空树的时候也是AVL树
		if(root == NULL)
			return true;
		int leftdepth = _Depth(root->_left);
		int rightdepth = _Depth(root->_right);
		if((rightdepth-leftdepth) != root->_bf)
		{
			cout<<"平衡因子异常："<<root->_key<<endl;
		}
		return abs(rightdepth-leftdepth)<=1
			&& _IsBalance(root->_left)
			&& _IsBalance(root->_right);
	}

	//经过优化后判断是否是平衡二叉树
	//思路分析：只遍历一次，每次进行递归回去的返回值
	//          是将上一次的高度带回
	//时间复杂度是O（N*N）
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
		//先进行判断此节点的左右子树是否是平衡二叉树
		if(_IsBalanceOP(root->_left,leftdepth)
			&& _IsBalanceOP(root->_right,rightdepth))
		{
			//如果是的话。那么就再来进行判断此节点是平衡二叉树
			//并且将左右节点中高度带回
			depth = leftdepth > rightdepth? leftdepth+1:rightdepth+1;
			return abs(leftdepth-rightdepth) < 2;
		}
		return false;
		
	}

		//中序遍历
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
	//左单旋
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

	//右单旋
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

	/*//左右旋转
	void RotateLR(Node* parent)
	{
		Node* cur = parent->_left;
		RotateL(cur);
		RotateR(cur);
	}
	
	//右左旋转
	void RotateRL(Node* parent)
	{
		Node* cur = parent->_right;
		RotateR(cur);
		RotateL(cur);
	}*/
	/***************经过细分情况的双旋*****************/
	//左右旋
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
	//右左旋
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
	//求平衡二叉树的高度
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