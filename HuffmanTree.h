//#include<iostream>
#include"Heap.h"
//using namespace std;
template<class T>
struct HuffmanTreeNode
{
	T _weight;
	HuffmanTreeNode<T>* _left;
	HuffmanTreeNode<T>* _right;
	HuffmanTreeNode<T>* _parent;
	HuffmanTreeNode(const T& x)
		:_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_weight(x)
	{}

	HuffmanTreeNode operator+(const HuffmanTreeNode& x)
	{
		return _weight+x._weight;
	}
};
template<class T>
class HuffmanTree
{
public:
	typedef HuffmanTreeNode<T> Node;
public:
	Node operator+(const Node& x)
		{
			return _weight+x._weight;
		}
	//构造函数
	HuffmanTree()
		:_root(NULL)
	{}
	HuffmanTree(T*a, size_t n,const T& invalue)
	{
		//因为在构建哈夫曼数的时候，比较的是两个权重的大小
		//而权重的类型是Node*，所以要进行重载
		struct com
		{
			bool operator()(Node* l,Node* r)
			{
				return l->_weight < r->_weight;
			}
			
		};
		//利用堆来实现数据的存储
		Heap<Node* ,com> hp;
		for(size_t i = 0; i<n; i++)
		{
			if(a[i] != invalue)
			hp.Push(new Node(a[i]));
		}
		//然后再进行构建哈夫曼树
		//构建的最后，数组里会只剩下一个元素
		while(hp.Size()>1)
		{
			//先取出堆顶的元素给左孩子
			Node* left = hp.Top();
			//出堆
			hp.Pop();
			//再取出堆顶的元素给右孩子
			Node* right = hp.Top();
			//出堆
			hp.Pop();
			//然后左右构建出一个父节点，即两者的权重之和
			//（注意：此处需要进行重载+）
			Node* parent = new Node(left->_weight+right->_weight);
			//将节点要进行连接
			parent->_left = left;
			parent->_right = right;
			//下面的这两条语句用于构建三叉链
			right->_parent = parent;
			left->_parent = parent;
			//要将构建完后的节点扔回来，因为它可能不是最小的
			hp.Push(parent);
		}
		//出循环后，数组中的存储就剩最后的一个节点，此节点就是根
		_root = hp.Top();
	}
	//析构函数
	~HuffmanTree()
	{
		if(_root)
			Destory(_root);
		_root = NULL;
	}
	void Destory(Node* root)
	{
		if(root == NULL)
			return;
		Destory(root->_left);
		Destory(root->_right);
		delete root;
	}

protected:
	Node* _root;
};





//说明：读者在具体实现的时候，将下面的这个文件重新定义成新的头文件
#ifndef __HEAP__
#define __HEAP__
#include<iostream>
#include<vector>
using namespace std;
template<class T>
struct Less
{
	bool operator()(const T& a,const T& b)
	{
		return a<b;
	}
};
template<class T>
struct Greater
{
	bool operator()(const T& a,const T& b)
	{
		return a>b;
	}
};

template<typename T,class com = Greater<int>>
class Heap
{
public:
	//构造函数
	Heap()
	{}
	//建堆
	Heap(T* a, size_t n)
		:_a(a,a+n)
	{
		/*_a.reserve(n);
		for(size_t i = 0; i<n; i++)
		{
			_a.push_back(a[i]);
		}*/
		for(int i = (_a.size()-2)/2; i>=0; i--)
		{
			_Adjustdown(i);
		}
	}
	//尾插
	void Push(const T& x)
	{
		_a.push_back(x);
		_Adjustup(_a.size()-1);
	}
	//尾删
	void Pop()
	{
		swap(_a[0],_a[_a.size()-1]);
		_a.pop_back();
		_Adjustdown(0);
	}
	//求堆里元素的个数
	size_t Size()
	{
		return _a.size();
	}
	//求堆顶的元素
	T& Top()
	{
		return _a[0];
	}
	//判断堆是否为空
	bool Empty()
	{
		return _a.size()==0;
	}
	
protected:
	//向下调整
	void _Adjustdown(int root)
	{
		int parent = root;
		int child = parent*2+1;
		//此处的条件有两个：
		//一个是当孩子的值小于父母的值时候这个已经在break处理过了
		//第二个条件就是当是叶子节点的时候
		while(child<_a.size())
		{
			//找左右孩子中值最大的
			if(child+1<_a.size() && com()(_a[child+1],_a[child]))
			{
				++child;
			}
			//将孩子和父母做比较
			if(com()(_a[child],_a[parent]))
			{
				swap(_a[child],_a[parent]);
				parent = child;
				child = parent*2+1;
			}
			else
			{
				break;
			}
		}
	}
	//向上调整
	void _Adjustup(int i)
	{
		//Compare com;
		int child = i;
		int parent = (i-1)/2;
		while(child >= 0)
		{
			if(com()(_a[child] , _a[parent]))
			{
				swap(_a[child],_a[parent]);
				child = parent;
				parent = (parent-1)/2;
			}
			else
			{
				break;
			}
		}
	}
protected:
	vector<T> _a;
};

#endif