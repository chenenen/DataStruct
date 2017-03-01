//说明：
//1、布隆过滤器有误判，所以一次性得多映射几个
//2、它是借助位图进行实现
//3、

#pragma once
#include"BitMap.h"
using namespace std;

template <typename K>
struct _BitFunc1
{
    size_t BKDRHash(const char *str)
    {
        register size_t hash = 0;
        while (size_t ch = (size_t)*str++)
        {
            hash = hash * 131 + ch;             
        }
        return hash;
    }

    size_t operator()(const string& key)
    {
        return BKDRHash(key.c_str());
    }
};
template<typename K>
struct _BitFunc2
{
    size_t SDBMHash(const char *str)
    {
        register size_t hash = 0;
        while (size_t ch = (size_t)*str++)
        {
            hash = 65599 * hash + ch;
        }
        return hash;
    }
    size_t operator()(const string& key)
    {
        return SDBMHash(key.c_str());
    }
};
template<typename K>
struct _BitFunc3
{
    size_t RSHash(const char *str)
    {
        register size_t hash = 0;
        size_t magic = 63689;
        while (size_t ch = (size_t)*str++)
        {
            hash = hash * magic + ch;
            magic *= 378551;
        }
        return hash;
    }
    size_t operator()(const string& key)
    {
        return RSHash(key.c_str());
    }
};
template<typename K>
struct _BitFunc4
{
    size_t RSHash(const char *str)
    {
        register size_t hash = 0;
        size_t ch;
        for (long i = 0; ch = (size_t)*str++; i++)
        {
            if ((i & 1) == 0)
            {
                hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
            }
            else
            {
                hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
            }
        }
        return hash;
    }
    size_t operator()(const string& key)
    {
        return RSHash(key.c_str());
    }
};

template<typename K>
struct _BitFunc5
{
    size_t RSHash(const char *str)
    {
        if (!*str)        // 这是由本人添加，以保证空字符串返回哈希值0  
            return 0;
        register size_t hash = 1315423911;
        while (size_t ch = (size_t)*str++)
        {
            hash ^= ((hash << 5) + ch + (hash >> 2));
        }
        return hash;
    }
    size_t operator()(const string& key)
    {
        return RSHash(key.c_str());
    }
};

template<typename K = string, 
    typename  BitFunc1 = _BitFunc1<K>,
    typename  BitFunc2 = _BitFunc2<K>,
    typename  BitFunc3 = _BitFunc3<K>,
    typename  BitFunc4 = _BitFunc4<K>,
    typename  BitFunc5 = _BitFunc5<K> >
class BloomFilter
{
public:
    //构造函数
    BloomFilter(const size_t num)
        : _size(num*10)
        , _bmf(num*5*2)
    {   
    }
    //布隆过滤器进行设置，根据原理，对通过字符串函数所计算的K个位进行设置状态。
     void SetBloomFilter(const K& key)
    {
        size_t index1 = BitFunc1()(key.c_str())%_size;
        size_t index2 = BitFunc2()(key.c_str())%_size;
        size_t index3 = BitFunc3()(key.c_str())%_size;
        size_t index4 = BitFunc4()(key.c_str())%_size;
        size_t index5 = BitFunc5()(key.c_str())%_size;

		_bmf.SetMap(index1);
        cout << index1 <<" ";

       _bmf.SetMap(index2);
        cout << index2 <<" ";

        _bmf.SetMap(index3);
        cout << index3 <<" ";

       _bmf.SetMap(index4);
        cout << index4 <<" ";

       _bmf.SetMap(index5);
        cout << index5 <<" ";

		cout<<endl;
    }


     bool TestBloomFilter(const K& key)
     {
         size_t index1 = BitFunc1()(key.c_str() )% _size;
		 if (_bmf.TestMap(index1) == 0)
         {
             return false;
         }
         size_t index2 = BitFunc2()(key.c_str()) % _size;
		 if (_bmf.TestMap(index2) == 0)
         {
             return false;
         }
         size_t index3 = BitFunc3()(key.c_str()) % _size;
		 if (_bmf.TestMap(index3) == 0)
         {
             return false;
         }
         size_t index4 =BitFunc4()(key.c_str() )% _size;
		 if (_bmf.TestMap(index4) == 0)
         {
             return false;
         }
         size_t index5 = BitFunc5()(key.c_str() )% _size;
		 if (_bmf.TestMap(index5) == 0)
         {
             return false;
         }
         return true;
     }

protected:
    BitMap _bmf;
    size_t _size;
};

void TestBloomFilter()
{
	BloomFilter<> bf(10);
	bf.SetBloomFilter("http://www.people.com.cn/");
	bf.SetBloomFilter("http://www.xinhuanet.com/");
	bf.SetBloomFilter("http://blog.csdn.net/lalu58");
	//bf.SetBloomFilter("http://blog.csdn.net/f11155667788");

	cout<<bf.TestBloomFilter("http://blog.csdn.net/lalu58");
	cout<<endl;
	cout<<bf.TestBloomFilter("http://blog.csdn.net/f11155667788");



}