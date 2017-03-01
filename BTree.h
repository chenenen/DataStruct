#include<iostream>
#include<map>
using namespace std; 
template<class K,class V,size_t M = 3>
struct BTreeNode
{
	pair<K,V> _kvs[M];          //值的个数
	BTreeNode<K,V>* _subs[M+1]; //子树的个数
	size_t _size;               //kv的大小
	BTreeNode<K,V>* _parent;

	BTreeNode(const pair<K,V>& kvs = pair<K,V>())
	{
		_parent = NULL;
		_size = 0;
		for(int i = 0; i<M+1; i++)
		{
			_subs[i] = NULL;
		}
		
	}
};
template<class K,class V,size_t M = 3>
class BTree
{
	typedef BTreeNode<K,V,M> Node;
public:
	//构造函数
	BTree()
		:_root(NULL)
	{}

	//查找函数
	pair<Node* ,int>Find(const pair<K,V>& kv)
	{
		Node* cur = _root;
		Node* parent = NULL;

		if(_root == NULL)
			return make_pair((Node*)NULL,-1);

		while(cur)
		{
			size_t i = 0;
			while(i<cur->_size)
			{
				//如果你寻找的这个值小于当前值的话
				if(cur->_kvs[i].first > kv.first)
				{
					
					break;
				}
				else if(cur->_kvs[i].first < kv.first)
				{
					++i;
				}
				else
				{
					return make_pair(cur,1);
				}

			}
			//到这里的话，就说明是要在子树中进行查找的
			parent = cur;
			cur = cur->_subs[i];

		}
		return make_pair(parent,-1);
	}

	//插入函数
	bool Insert(const pair<K,V>& kv)
	{
		//先进行根节点的判断
		if(_root == NULL)
		{
			_root = new Node;
			_root->_kvs[0] = kv;
			
			_root->_size++;
			return true;
		}
		//在判断要插入的节点是否存在
		pair<Node*,V> ret = Find(kv);
		//如果要插入的节点已经存在的话，则直接返回假
		if(ret.second != -1)
			return false;

		Node* cur = ret.first;
		pair<K,V> newkv = kv;
		Node* sub = NULL;

		//否则要进行插入
		while(1)
		{
			_InsertKV(cur,newkv,sub);

			//如果插入值之后没有满的话，就直接返回，否则就进行分裂
			if(cur->_size < M)
				return true;

			//到这一步进行分裂
			Node* temp = new Node;  //先创建一个节点
			size_t mid = M/2;
			size_t j = 0;    //作为新分裂的节点的下标
			size_t i = mid+1;

			for(; i<cur->_size; i++)
			{
				temp->_kvs[j] = cur->_kvs[i];
				cur->_kvs[i] = pair<K,V>();

				temp->_subs[j] = cur->_subs[j];

				if(cur->_subs[i])
					cur->_subs[i]->_parent = temp;

				temp->_size++;
				++j;
			}
			//拷走最后一个右孩子
			temp->_subs[j] = cur->_subs[i];
			if(cur->_subs[i])
				cur->_subs[i]->_parent = temp;
			cur->_size = cur->_size-temp->_size-1;

			//将分裂的节点kv和temp向父节点插入（向上调整）
			//分两种情况：cur的父节点为空的时候和不为空的时候
			if(cur->_parent == NULL)
			{
				_root = new Node;
				_root->_kvs[0] = cur->_kvs[mid];
				cur->_kvs[mid] = pair<K,V>();
				_root->_size = 1;
				cur->_size--; //在进行向上调整后要将原来节点的size--

				_root->_subs[0] = cur;
				_root->_subs[1] = temp;

				cur->_parent = _root;
				temp->_parent = _root;

				return true;
			}
			else
			{
				newkv = cur->_kvs[mid];
				sub = temp;
				cur->_kvs[mid] = pair<K,V>();
				cur = cur->_parent;
			}
		}
	}


	//中序遍历
	void InOrder()
	{
		_InOrder(_root);
	}

protected:
	//在cur节点插入newKV和sub
	void _InsertKV(Node* cur,pair<K,V>& kvs,Node* sub)
	{
		int i = cur->_size-1;
		while(i >= 0)
		{
			if(cur->_kvs[i].first < kvs.first)
			{
				break;
			}
			else
			{
				cur->_kvs[i+1] = cur->_kvs[i];
				cur->_subs[i+2] = cur->_subs[i];
			}
			i--;
		}
		cur->_kvs[i+1] = kvs;
		cur->_subs[i+2] = sub;
		++cur->_size;
	}


	//中序遍历
	void _InOrder(Node* root)
	{
		if(root == NULL)
			return;
		Node* cur = root;
		size_t i = 0;
		for(; i<cur->_size; i++)
		{
			_InOrder(cur->_subs[i]);
			cout<<cur->_kvs[i].first<<" ";
		}
		_InOrder(cur->_subs[i]);
	}
protected:
	Node* _root;
};
void TestBTree()
{
	BTree<int, int> bt;
	int a[] = {53, 75, 139, 49, 145, 36, 101};
	for (size_t i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
	{
		bt.Insert(make_pair(a[i], i));
	}

	bt.InOrder();

}