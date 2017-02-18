#include<iostream>
#include<vector>
using namespace std;

//表中存储元素的状态
enum Status
{
	EMPTY,
	DELETE,
	EXIST,
};

template<class K, class V>
struct HashNode
{
	K _key;
	V _value;
	Status _status;

	HashNode(const K& key = K(),const V& value = V())
		:_key(key)
		,_value(value)
		,_status(EMPTY)
	{}
};

//仿函数
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
	//此处用静态的，在main函数执行前只生成一次
	static size_t BKDRHash(const char *str)  
	{  
		register size_t hash = 0;  
		while (size_t ch = (size_t)*str++)  
		{     
			//131是研究出来的数字，使用这个公式，就会避免重复
			hash = hash * 131 + ch;         
		}  
		return hash;  
	}
	 size_t operator ()(const string &key)
        {
            return BKDRHash(key.c_str());
        }
};
template<typename K,typename V,typename HashFunc = _HashFunc<K>>
class HashTable
{
	typedef HashNode<K,V> Node;
public:

	//构造函数
	HashTable(size_t size)
		:_size(0)
	{
		//_ht.resize(size);
		_ht.resize(GetNewSize);
	}
	
	//交换函数
	void Swap(HashTable& spht)
	{
		_ht.swap(spht._ht);
	}
	//扩容函数
	void CheckCapacity()
	{
		//如果哈希表是空的或者它的容量已经超过了负载因子，就要进行扩容
		if(_ht.size() == 0 || (_size*10)/_ht.size() >= 7)
		{
			size_t newsize = _size*2+3;
			HashTable temp(0);
			temp._ht.resize(newsize);
			for(int i = 0; i<_size; i++)
			{
				if(_ht[i]._status == EXIST)
				temp.Insert(_ht[i]._key,_ht[i]._value);
			}
			this->Swap(temp);
		}
	}


	//插入元素的函数
	bool Insert(const K& key,const V& value)
	{
		//检测是否需要扩容
		CheckCapacity();
		size_t index = _HashFunc(key);
		
		while(_ht[index]._status == EXIST)
		{
			if(_ht[index]._key == key)
				return false;

			++index;
			if(index == _ht.size()) //这块注意
				index = 0;
		}	
		++_size;
		_ht[index]._key = key;
		_ht[index]._value = value;
		_ht[index]._status = EXIST;
		return true;

	}

	//寻找元素的函数
	Node* Find(const K& key)
	{
		size_t i = _HashFunc(key);
		while(_ht[i]._status != EMPTY)
		{
			if(_ht[i]._key == key && _ht[i]._status == EXIST)
				return &_ht[i];
			++i;
			if(i == _ht.size())
				i = 0;
		}
		
		return NULL;
	}
	
	//哈希函数
	size_t _HashFunc(const K& key)
	{
		HashFunc hf;
		return hf(key)%(_ht.size());
	}

protected:
	//使用素数表来解决哈希冲突
	//使用素数表作为哈希表的容量，作为除数
	//其实就是多扩容了
	size_t GetNewSize()
	{
		const int _PrimeSize = 28;
		//采用素数表
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
	vector<Node> _ht;
	size_t _size; //哈希表的容量
};

//测试
void TestHashTable()
{
	HashTable<int,int> ht(10);
	ht.Insert(49,0);
	ht.Insert(58,1);
	ht.Insert(9,2);
	ht.Insert(0,3);
	ht.Insert(0,4);
	ht.Insert(0,5);
	ht.Insert(0,6);
	ht.Insert(0,7);
	ht.Insert(18,8);
	ht.Insert(89,9);

	ht.Find(9);
	ht.Find(10);

	


	
}