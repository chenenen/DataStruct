#include<iostream>
#include<map>
using namespace std; 
template<class K,class V,size_t M = 3>
struct BTreeNode
{
	pair<K,V> _kvs[M];          //ֵ�ĸ���
	BTreeNode<K,V>* _subs[M+1]; //�����ĸ���
	size_t _size;               //kv�Ĵ�С
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
	//���캯��
	BTree()
		:_root(NULL)
	{}

	//���Һ���
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
				//�����Ѱ�ҵ����ֵС�ڵ�ǰֵ�Ļ�
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
			//������Ļ�����˵����Ҫ�������н��в��ҵ�
			parent = cur;
			cur = cur->_subs[i];

		}
		return make_pair(parent,-1);
	}

	//���뺯��
	bool Insert(const pair<K,V>& kv)
	{
		//�Ƚ��и��ڵ���ж�
		if(_root == NULL)
		{
			_root = new Node;
			_root->_kvs[0] = kv;
			
			_root->_size++;
			return true;
		}
		//���ж�Ҫ����Ľڵ��Ƿ����
		pair<Node*,V> ret = Find(kv);
		//���Ҫ����Ľڵ��Ѿ����ڵĻ�����ֱ�ӷ��ؼ�
		if(ret.second != -1)
			return false;

		Node* cur = ret.first;
		pair<K,V> newkv = kv;
		Node* sub = NULL;

		//����Ҫ���в���
		while(1)
		{
			_InsertKV(cur,newkv,sub);

			//�������ֵ֮��û�����Ļ�����ֱ�ӷ��أ�����ͽ��з���
			if(cur->_size < M)
				return true;

			//����һ�����з���
			Node* temp = new Node;  //�ȴ���һ���ڵ�
			size_t mid = M/2;
			size_t j = 0;    //��Ϊ�·��ѵĽڵ���±�
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
			//�������һ���Һ���
			temp->_subs[j] = cur->_subs[i];
			if(cur->_subs[i])
				cur->_subs[i]->_parent = temp;
			cur->_size = cur->_size-temp->_size-1;

			//�����ѵĽڵ�kv��temp�򸸽ڵ���루���ϵ�����
			//�����������cur�ĸ��ڵ�Ϊ�յ�ʱ��Ͳ�Ϊ�յ�ʱ��
			if(cur->_parent == NULL)
			{
				_root = new Node;
				_root->_kvs[0] = cur->_kvs[mid];
				cur->_kvs[mid] = pair<K,V>();
				_root->_size = 1;
				cur->_size--; //�ڽ������ϵ�����Ҫ��ԭ���ڵ��size--

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


	//�������
	void InOrder()
	{
		_InOrder(_root);
	}

protected:
	//��cur�ڵ����newKV��sub
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


	//�������
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