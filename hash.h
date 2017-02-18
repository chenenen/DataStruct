#include<iostream>
#include<vector>
using namespace std;

//���д洢Ԫ�ص�״̬
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

//�º���
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
template<typename K,typename V,typename HashFunc = _HashFunc<K>>
class HashTable
{
	typedef HashNode<K,V> Node;
public:

	//���캯��
	HashTable(size_t size)
		:_size(0)
	{
		//_ht.resize(size);
		_ht.resize(GetNewSize);
	}
	
	//��������
	void Swap(HashTable& spht)
	{
		_ht.swap(spht._ht);
	}
	//���ݺ���
	void CheckCapacity()
	{
		//�����ϣ���ǿյĻ������������Ѿ������˸������ӣ���Ҫ��������
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


	//����Ԫ�صĺ���
	bool Insert(const K& key,const V& value)
	{
		//����Ƿ���Ҫ����
		CheckCapacity();
		size_t index = _HashFunc(key);
		
		while(_ht[index]._status == EXIST)
		{
			if(_ht[index]._key == key)
				return false;

			++index;
			if(index == _ht.size()) //���ע��
				index = 0;
		}	
		++_size;
		_ht[index]._key = key;
		_ht[index]._value = value;
		_ht[index]._status = EXIST;
		return true;

	}

	//Ѱ��Ԫ�صĺ���
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
	
	//��ϣ����
	size_t _HashFunc(const K& key)
	{
		HashFunc hf;
		return hf(key)%(_ht.size());
	}

protected:
	//ʹ���������������ϣ��ͻ
	//ʹ����������Ϊ��ϣ�����������Ϊ����
	//��ʵ���Ƕ�������
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
	vector<Node> _ht;
	size_t _size; //��ϣ�������
};

//����
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