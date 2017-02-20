#include<iostream>
#include<vector>
#include<string>
using namespace std; 

//�ڵ�Ķ���
template<class K,class V>
struct HushNode
{
	K _key;
	V _value;

	HushNode<K,V>* _next;
	HushNode(const K& key,const V& value)
		:_key(key)
		,_value(value)
		,_next(NULL)
	{}
};

//��������ʵ��
template<class K,class V,class Ref,class Ptr>
struct HushInterator
{
	typedef HushNode<K,V> Node;
	typedef HushIterartor<K,V,Ref,Ptr> Self;

	Node* _node;
	HushTable<K,V>* _ht;
	
	//���캯����ʵ��
	HushIterartor(Node* node,HushTable<K,V>* ht)
		:_node(node)
		,_ht(ht)
	{}

	//����������ʵ��
	Ref operator*(Node* node)
	{
		return node->_key;
	}

	Ptr operator->(Node* node)
	{
		return &(node->_key);
	}

	bool operator==(const Self& s)
	{
		return _node == s.node;
	}

	bool operator!=(const Self& s)
	{
		return _node!=s.node;
	}

	Self& operator++()
	{
		_node = Next(node);
		//return _node;
		return *this;
	}

protected:
	Node* Next(Node* node)
	{
		Node* next = node->_next;
		//�����һ���ڵ㲻Ϊ�յĻ�ֱ�ӷ����������ڵ�
		if(next)
			return next;
		//�����һ���ڵ�Ϊ�յĻ���ȥ�Ҳ�Ϊ�յĽ��䷵��
		else
		{
			size_t index = _ht->_HushFunc(node->_key)+1;
			for(int i = 0; i<_ht->_ht.size(); i++)
			{
				next = _ht->_ht[index];
				if(next)
					return next;
			}
		}
		return NULL;
	}

};

//�º�����ʵ��
template<class K>
struct _HashFunc
{
	size_t operator()(const K& key)
	{
		return key;
	}
};
template<>
struct _HashFunc<string>
{
	//�˴��þ�̬�ģ���main����ִ��ǰֻ����һ��
	static size_t BKDRHash(const char *str)  
	{  
		register size_t hash = 0;  
		while (size_t ch = (size_t)*str++)  
		{     
			//131���о����������֣�ʹ�������ʽ���ͻ�����ظ�
			hash = hash * 131 + ch;         
		}  
		return hash;  
	}
	size_t operator ()(const string &key)
	{
		return BKDRHash(key.c_str());
	}
};


//��ϣ���ʵ�֣�ͨ����ϣͰ��
template<class K,class V,class HushFunc = _HushFunc<K>>
class HushTable
{
	typedef HushNode<K,V> Node;
public:
	typedef HushIterator<K,V,pair<K,V>*,pair<K,V>&> Iterator;
	typedef HushIterator<K,V,const pair<K,V>*,const pair<K,V>&> ConstIterator;	
public:
	//���캯����ʵ��
	HushTable()
		:_size(0)
	{
		_ht.resize(GetNewSize());
	}
	HushTable(size_t size)
		:_size(0)
	{
		_ht.resize(GetNewSize());
	}


	//���뺯����ʵ��
	pair<Node*, bool> Insert(const K& key, const V& value)
	{
		//����֮ǰҪ�Ƚ����Ƿ����ݵļ��
		CheckCapacity();
		//�ҵ��������λ��
		size_t index = _HushFunc(key);
		Node* cur = _ht[index];
		while(cur)
		{
			if(cur->_key == key)
				return make_pair(cur,false);
			cur = cur->_next;
		}
		Node* temp = new Node(key,value);
		temp->_next = _ht[index];
		_ht[index] = temp;
		return make_pair(temp,true);
	}

	//ɾ��������ʵ��
	void Erase(const K& key)
	{
		//�Ƚ��в����������λ��
		size_t index = _HushFunc(key);
		Node* pre = NULL;
		Node* cur = _ht[index];
		//ɾ����ʱ��Ҫ��������ķ�������
		while(cur)
		{
			if(pre == NULL)
			{
				_ht[index] = cur->_nex;
				delete cur;
			}
			else
			{
				pre->_next = cur->_next;
			}
			cur = cur->_next;

		}

	}

	//���Һ�����ʵ��
	Node* Find(const K& key)
	{
		for(int i = 0; i<_size; i++)
		{
			Node* cur = _ht[i];
			while(cur)
			{
				if(cur->_key == key)
					return cur;
				cur = cur->_next;
			}
		}
		return NULL;
	}

	//��ϣ������ʵ��
	size_t _HushFunc(const K& key)
	{
		HushFunc hf;
		return hf(key)%_ht.size(); 
	}

	//����������ʵ��
	~HushTable()
	{
		for(size_t i = 0; i<_size; i++)
		{
			Node* del = NULL;
			Node* cur = _ht[i];
			while(cur)
			{
				del = cur;
				cur = cur->_next;
				delete del;
			}
		}
	}


protected:

	//��ʼ�ͽ�β��������ʵ��
	///*Iterator Begin()
	//{
	//	for(i = 0; i<_ht.size(); i++)
	//	{
	//		if(_ht[i])
	//			return iterator (_ht[i],this);
	//	}
	//}
	//Iterator End()
	//{
	//	return Iterator(NULL,this);
	//}*/
	//���ݺ�����ʵ��
	void CheckCapacity()
	{
		//����ϣ��Ϊ�յ�ʱ����߸�������Ϊ1��ʱ��,��������
		if(_ht.size() == 0 || _size/_ht.size() == 1)
		{
			//��һ���±�
			HushTable temp;
			size_t newsize = GetNewSize();
			temp._ht.resize(newsize);

			//��Ԫ�طŽ�ȥ
			for(int i= 0; i<_ht.size(); i++)
			{
				Node* cur = _ht[i];
				while(cur)
				{
					temp.Insert(cur->_key,cur->_value);
					cur = cur->_next;
				}
			}
		}
	}

	//����������ʵ��
	void Swap(HushTable<K,V>& htb)
	{
		_ht.swap(spht._hbt);
	}

	//ʹ������������ϣ��ͻ
	//ʹ��������õ�����
	size_t GetNewSize()
	{
		const int _PrimeSize = 28;
		//����������
		static const unsigned long _PrimeList[_PrimeSize] =
		{
			53ul, 97ul, 193ul, 389ul, 769ul,
			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
			49157ul, 98317ul, 196613ul, 393241ul,
			786433ul,
			1572869ul, 3145739ul, 6291469ul, 12582917ul,
			25165843ul,
			50331653ul, 100663319ul, 201326611ul, 402653189ul,
			805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};
		for (size_t i = 0; i < _PrimeSize; ++i)
		{
			if (_ht.size() < _PrimeList[i])
			{
				return _PrimeList[i];
			}
		}
		return 0;
	}
protected:
	vector<Node*> _ht;
	size_t _size;
};

//���Ժ���
void TestBucket()
{
	HushTable<int,int> ht;
	ht.Insert(0,0);
	ht.Insert(53,0);
	ht.Insert(106,0);
	ht.Insert(2,0);
	ht.Insert(55,0);
	ht.Insert(3,0);
	ht.Insert(51,0);
	ht.Insert(52,0);
	ht.Insert(105,0);


	//	HushTable<int,int>::Iterator it1 = ht.Begin();
	//	while(it1 != ht.End())
	//	{
	//		cout<<*it1<<" ";
	//		it1++;
	//	}
	//	cout<<endl;
	//}
}
