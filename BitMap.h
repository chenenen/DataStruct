#include<iostream>
#include<vector>
using namespace std;
class BitMap
{
public:
	//λͼ�Ĺ���
	BitMap(size_t N = 1024) //
	{
		_bm.resize((N/32)+1);  //ע��˴�����������ȼ�
	}
	//����λͼ�ķ�ʽ������ֵ����λ
	void SetMap(size_t v)
	{
		//ͨ�����õ���������һ���±��д洢��
		size_t index = v>>5;
		//ͨ��ģ�õ������ľ���λ��
		size_t num = v%32;
		//���������ڵ�λ����Ϊ1
		_bm[index] |= (1<<num);

	}
	//������ֵ�ĸ�λ
	void RetsetMap(size_t v)
	{
		size_t index = v>>5;
		size_t num = v%32;

		_bm[index] &= ~(1<<num);
	}
	//����һ����������������Ƿ���
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