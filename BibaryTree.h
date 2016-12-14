#include<iostream>
using namespace std;
#include<assert.h>
#include<queue>
template<typename T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T>* _left;  //左孩子
	BinaryTreeNode<T>* _right; //右孩子
	BinaryTreeNode(const T&x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
	{}
};
template<typename T>
class BinaryTree
{
public:
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()
		:_root(NULL)	
	{}
	//构造函数
	BinaryTree(T* a, size_t size,const T& invalue = T())
	{
		assert(a);
		size_t index = 0;
		_root = CreatTree(a,size,index,invalue);
	}
	Node* CreatTree(T* a,size_t size,size_t &index,const T& invalue = T())
	{
		//Node* root = NULL;
		if(index<size && a[index] != invalue)
		{
			Node* newroot= new Node(a[index]);
			//root->_data = a[index];
			newroot->_left = CreatTree(a,size,++index,invalue);
			newroot->_right = CreatTree(a,size,++index,invalue);
			return newroot;
		}
		return NULL;//root;
	}
	//拷贝构造函数
	BinaryTree(const BinaryTree<T>&x)
	{
		_root = Copy(x._root);
	}
	Node* Copy(Node* root)
	{
		if(root)
		{
			Node* cur = new Node(root->_data);
			cur->_left = Copy(root->_left);
			cur->_right = Copy(root->_right);
			return cur;
		}
		return NULL;
	}
	//赋值运算符重载
	BinaryTree& operator=(const BinaryTree<T>&x)
	{
		if(this != &x)
		{
			Node* temp = Copy(x._root);
			if(_root)
				Destory(_root);
			_root = temp;
		}
		return *this;
	}
	//析构函数
	~BinaryTree()
	{
		if(_root)
		{
			Destory(_root);
		}
		_root = NULL;
	}
	void Destory(Node* root)
	{
		if(root == NULL)
			return;
		if(root->_left == NULL && root->_right == NULL)
		{
			delete root;
			return;
		}
		Destory(root->_left);
		root->_left = NULL;
		Destory(root->_right);
		root->_right = NULL;
	}
	//前序遍历
	void PrevOrder()
	{
		_PrevOrder(_root);
		cout<<endl;
	}
	void _PrevOrder(Node* root)
	{
		if(root)
		{
			cout<<root->_data<<" ";
			_PrevOrder(root->_left);
			_PrecOrder(root->_right);
		}
	}
	//中序遍历
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
	void _InOrder(Node* root)
	{
		if(root)
		{
			_InOrder(root->_left);
			cout<<root->_data<<" ";
			_InOrder(root->_right);
		}
	}
	//后序遍历
	void LaterOrder()
	{
		_LaterOrder(_root);
		cout<<endl;
	}
	void _LaterOrder(Node* root)
	{
		if(root)
		{
			_LaterOrder(root->_left);
			_LaterOrder(root->right);
			cout<<root->data<<" ";
		}
	}
	//层序遍历
	void LevelOrder()
	{
		_LeverOrder(_root);
		cout<<endl;
	}
	void _LevelOrder(Node* root)
	{
		if(root == NULL)
			return;
		queue<Node*> q;
		q.push(root);
		while(!q.empty())
		{
			queue<Node*> temp = q.front();
			cout<<q.front()<<endl;
			q.pop();
			if(temp->_left)
			{
				q.push(temp->_left);
			}
			if(temp->_right)
			{
				q.push(temp->_right);
			}
		}
	}
	//求二叉树的节点个数
	size_t Size()
	{
		return _Size(_root);
	}
	size_t _Size(Node* root)
	{
		if(root == NULL)
			return 0;
		return _Size(root->_left)+_Size(root->_right)+1;
	}
	//求二叉树的深度
	size_t Depth()
	{
		return _Depth(_root);
	}
	size_t _Depth(Node* root)
	{
		//size_t temp 
		if(root == NULL)
			return 0;
		if(root->_left == NULL && root->_right == NULL)
			return 1;
		size_t lefttemp = _Depth(root->_left);
		size_t righttemp = _Depth(root->_right);	
		return lefttemp>righttemp?lefttemp+1:righttemp+1;
		
	}
	//求第K层的节点数
	size_t GetklevelSize(size_t k)
	{
		assert(k>0);
		return _GetklevelSize(_root,k);
	}
	size_t _GetklevelSize(Node* root,size_t k)
	{
		if(root == NULL)
			return 0;
		if(k == 1)
			return 1;
		
		return _GetklevelSize(root->_left,k-1)+_GetklevelSize(root->_right,k-1);
		 
	}
	//求叶子节点的个数
	size_t GetleafSize()
	{
		return _GetleafSize(_root);
	}
	size_t _GetleafSize(Node* root)
	{
		size_t size = 0;
		if(root)
		{
			//当根的左右节点都为空的时候此根就是叶子节点，
			if(root->_left == NULL && root->_right == NULL)
			{
				size = size+1;
			}
			size += _GetleafSize(root->_left);
			size += _GetleafSize(root->_right);
		}
		return size;
	}
protected:
	Node* _root;
};

void Test()
{
	int a[10] = {1,2,3,'#','#',4,'#','#',5,6};
	BinaryTree<int> t1(a,sizeof(a)/sizeof(a[0]),'#');
	cout<<t1.Depth()<<endl;
	cout<<t1.Size()<<endl;
	t1.InOrder();
	cout<<t1.GetklevelSize(2)<<endl;
	cout<<t1.GetleafSize()<<endl;
	BinaryTree<int> t2(t1);
	BinaryTree<int> t3;
	t3 = t1;
	
}
