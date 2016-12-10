#include<iostream>
using namespace std;
template<typename T>
class SymmetricMatrix
{
public:
	//���캯��
	SymmetricMatrix()
	{}
	SymmetricMatrix(T* a, size_t n)
		:_a(new T[n*(n+1)/2])
		,_n(n)
	{
		size_t index = 0;
		for(size_t i= 0; i<_n; i++)
		{
			for(size_t j = 0; j<_n; j++)
			{
				if(i >= j)
				{
					_a[index] = a[i*n+j];//ע������
					index++;
				}
				else
				{
					break;
				}
			}
		}
	}
	//��������
	~SymmetricMatrix()
	{
		if(_a)
		{
			delete[]_a;
		}
	}
	//�ж������Ƿ��Ƿ��������ǵ�
	T& Access(size_t i,size_t j)
	{
		if(i <= j)
		{
			std::swap(i,j);
		}
		return _a[i*(i+1)/2+j];
	}
	//��ӡ�Գƾ���
	void Print()
	{
		for(size_t i = 0; i<_n; i++)
		{
			for(size_t j = 0; j<_n; j++)
			{			
				cout<<Access(i,j)<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
	}
protected:
	T* _a;      //�ö�ά����洢����һά������ж�ȡ 
	size_t _n;   //��Ϊ��n*n�ģ�ֱ�Ӹ�n�Ϳ�����

};
void Test()
{
	int a [5][5]=
	{
	{0,1,2,3,4},
	{1,0,1,2,3},
	{2,1,0,1,2},
	{3,2,1,0,1},
	{4,3,2,1,0},
	};
	SymmetricMatrix<int> sm((int*)a,5);
	sm.Print();
}
