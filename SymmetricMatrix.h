#include<iostream>
using namespace std;
template<typename T>
class SymmetricMatrix
{
public:
	//构造函数
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
					_a[index] = a[i*n+j];//注意问题
					index++;
				}
				else
				{
					break;
				}
			}
		}
	}
	//析构函数
	~SymmetricMatrix()
	{
		if(_a)
		{
			delete[]_a;
		}
	}
	//判断数组是否是访问下三角的
	T& Access(size_t i,size_t j)
	{
		if(i <= j)
		{
			std::swap(i,j);
		}
		return _a[i*(i+1)/2+j];
	}
	//打印对称矩阵
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
	T* _a;      //用二维数组存储，用一维数组进行读取 
	size_t _n;   //因为是n*n的，直接给n就可以了

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
