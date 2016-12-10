#include<iostream>
#include<vector>
using namespace std;
template<typename T>
struct Tripe
{
	Tripe()
	{}   //为resize()的第二个参数创建
	Tripe<T>(const T& x,size_t row,size_t col)
		:_value(x)
		,_row(row)
		,_col(col)
	{}
	T _value;   
	size_t _row;
	size_t _col;
};
template<typename T>
class SparseMatrix
{
public:
	//构造函数
	SparseMatrix()
	{}
	
	SparseMatrix(T* a,size_t m,size_t n,const T& invalue)
		:_a()
		,_rowSize(m)
		,_colSize(n)
		,_invalue(invalue)
	{
		for(size_t i = 0; i<m; i++)
		{
			for(size_t j=0; j<n; j++)
			{
				if(a[i*n+j] != invalue)
				{
					Tripe<T>temp(a[i*n+j],i,j);//先创建一个三元组的变量来存储你要放入矩阵里的数组元素
					_a.push_back(temp);  //再调用vector里的尾插进行压栈
				}
			}
		}
	}
	//打印三元组
	void Printp()
	{
		for(size_t i = 0; i<_a.size(); i++)
		{
			cout<<"col: "<<_a[i]._col
				<<"row: "<<_a[i]._row
				<<"value; "<<_a[i]._value<<endl;
		}
	}
	//打印稀疏矩阵
	void Print()
	{
		size_t index = 0;
		for(size_t i = 0; i<_rowSize; i++)
		{
			for(size_t j = 0; j<_colSize; j++)
			{
				if(index < _a.size() &&
					_a[index]._row == i &&
					_a[index]._col == j )
				{
					cout<<_a[index]._value<<" ";
					++index;
				}
				else
				{
					cout<<_invalue<<" ";
				}
			}
			cout<<endl;
		}
		cout<<endl;
	}
	//普通的转置:
	//方法说明：原来的列是转置后的行，然后进行列的遍历，依次放置
	SparseMatrix<T> Tranport()
	{
		//先创建转置后的数组
		size_t index = 0;
		SparseMatrix<T> sm;
		sm._rowSize = _colSize;//现在的行是原来的列
		sm._colSize = _rowSize;//现在的列是原来的行
		sm._invalue = _invalue;//无效值不变
		sm._a.reserve(_a.size());//是优化，首先开辟的是size大小；其次在Push_back的时候不会再去扩容了
		//开始从列查找
		for(size_t i = 0; i<_colSize; i++)
		{
			//遍历原来的整个容器
			for(size_t index = 0; index <_a.size(); index++)
			{
				if(_a[index]._col == i)
				{
					Tripe<T> temp(_a[index]._value,_a[index]._col,_a[index]._row);
					sm._a.push_back(temp);
				}
			}
		}
		return sm;
	}
	//快速转置：
	//方法说明：
	//1）定义两个数组：一个记录元素的起始位置的下标：
	 //               转置后的起始位置的下标
	//                 一个记录元素的个数：
	 //               转置后的一行中元素的个数就是转置前一列的元素个数
	//2）此元素=上一个元素的起始位置+上一个元素的个数
	//
	SparseMatrix<T> FastTranport()
	{
		SparseMatrix<T> sm;
		sm._rowSize = _colSize;
		sm._colSize = _rowSize;
		sm._invalue = _invalue;

		int* count = new int[_colSize];
		memset(count,0,sizeof(int)*_colSize);
		int* start = new int[_colSize];
		sm._a.resize(_a.size());   //下面是用下标访问的，用resize会比较合适
		size_t index = 0;
		while(index < _a.size())
		{
			count[_a[index]._col]++; //用原来列的有效数值位作为计数的下标
			++index;
		}
		start[0] = 0; //第一个数值一定是0
		for(size_t i = 1; i<_colSize; i++)
		{
			start[i] = start[i-1]+count[i-1];
		}
		index = 0;
		while(index<_a.size())
		{
			Tripe<T>temp(_a[index]._value,_a[index]._col,_a[index]._row);
			sm._a[start[_a[index]._col]++] = temp;
			++index;
		}
		delete[]count;
		delete[]start;
		return sm;
	}


private:
	vector<Tripe<T>> _a;
	size_t _rowSize;
	size_t _colSize;
	T _invalue;     //存储无用值
};
void Test()
{
	int array [6][5] = {{1, 0, 3, 0, 5},
						{0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0},
						{2, 0, 4, 0, 6},
							};
	SparseMatrix<int> sm((int*)array,6,5,0);
	sm.Print();
	sm.Printp();
	sm.Tranport().Print();
	sm.FastTranport().Print();
}
