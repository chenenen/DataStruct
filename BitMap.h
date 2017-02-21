#include<iostream>
#include<vector>
using namespace std;
class BitMap
{
public:
	//位图的构造
	BitMap(size_t N = 1024) //
	{
		_bm.resize((N/32)+1);  //注意此处的运算符优先级
	}
	//按照位图的方式进行数值的置位
	void SetMap(size_t v)
	{
		//通过除得到此数在哪一个下标中存储中
		size_t index = v>>5;
		//通过模得到此数的具体位置
		size_t num = v%32;
		//将此数存在的位置置为1
		_bm[index] |= (1<<num);

	}
	//进行数值的复位
	void RetsetMap(size_t v)
	{
		size_t index = v>>5;
		size_t num = v%32;

		_bm[index] &= ~(1<<num);
	}
	//给定一个数，测试这个数是否在
	bool TestMap(size_t v)
	{
		size_t index = v>>5;
		size_t num = v%32;

		return _bm[index] & (1<<num);
	}
protected:
	vector<size_t> _bm;
};

void TestBitMap()
{
	BitMap bm((size_t)-1);
	bm.SetMap(50);
	bm.SetMap(10);
	bm.SetMap(20);
	bm.SetMap(40);
	bm.SetMap(7);

	cout<<bm.TestMap(8)<<endl;
	cout<<bm.TestMap(7)<<endl;

}