#include<iostream>
#include<vector>
using namespace std;
template<typename T>
struct Tripe
{
	Tripe()
	{}   //Ϊresize()�ĵڶ�����������
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
	//���캯��
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
					Tripe<T>temp(a[i*n+j],i,j);//�ȴ���һ����Ԫ��ı������洢��Ҫ��������������Ԫ��
					_a.push_back(temp);  //�ٵ���vector���β�����ѹջ
				}
			}
		}
	}
	//��ӡ��Ԫ��
	void Printp()
	{
		for(size_t i = 0; i<_a.size(); i++)
		{
			cout<<"col: "<<_a[i]._col
				<<"row: "<<_a[i]._row
				<<"value; "<<_a[i]._value<<endl;
		}
	}
	//��ӡϡ�����
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
	//��ͨ��ת��:
	//����˵����ԭ��������ת�ú���У�Ȼ������еı��������η���
	SparseMatrix<T> Tranport()
	{
		//�ȴ���ת�ú������
		size_t index = 0;
		SparseMatrix<T> sm;
		sm._rowSize = _colSize;//���ڵ�����ԭ������
		sm._colSize = _rowSize;//���ڵ�����ԭ������
		sm._invalue = _invalue;//��Чֵ����
		sm._a.reserve(_a.size());//���Ż������ȿ��ٵ���size��С�������Push_back��ʱ�򲻻���ȥ������
		//��ʼ���в���
		for(size_t i = 0; i<_colSize; i++)
		{
			//����ԭ������������
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
	//����ת�ã�
	//����˵����
	//1�������������飺һ����¼Ԫ�ص���ʼλ�õ��±꣺
	 //               ת�ú����ʼλ�õ��±�
	//                 һ����¼Ԫ�صĸ�����
	 //               ת�ú��һ����Ԫ�صĸ�������ת��ǰһ�е�Ԫ�ظ���
	//2����Ԫ��=��һ��Ԫ�ص���ʼλ��+��һ��Ԫ�صĸ���
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
		sm._a.resize(_a.size());   //���������±���ʵģ���resize��ȽϺ���
		size_t index = 0;
		while(index < _a.size())
		{
			count[_a[index]._col]++; //��ԭ���е���Ч��ֵλ��Ϊ�������±�
			++index;
		}
		start[0] = 0; //��һ����ֵһ����0
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
	T _invalue;     //�洢����ֵ
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
