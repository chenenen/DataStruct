#include<iostream>
using namespace std; 
#include<vector>
#include<assert.h>
#include<string>
//说明：用邻接矩阵的方式表示图
template<class V,class W>
class GraphMatrix
{
public:
	//构造函数
	GraphMatrix(V* v,size_t n,bool isDirected = false,const W& invalue = W())
		:_v(v,v+n)
		,_isDirected(isDirected)
	{
		_matrix = new W*[_v.size()];
		for(size_t i = 0; i<n; i++)
		{
			_matrix[i] = new W[_v.size()];
			for(size_t j = 0; j<n; j++)
			{
				_matrix[i][j] = invalue;
			}
		}
	}

	//给定一个顶点，如何得到这个顶点的下标
	size_t GetIndex(const V& v)
	{
		for(size_t i = 0; i<_v.size(); i++)
		{
			if(_v[i] == v)
			{
				return i;
			}
		}
		assert(false);
		return 0;
	}
	//如何加一条边
	void AddEge(const V& v1, const V& v2, const W& w)
	{
		size_t src = GetIndex(v1);
		size_t dest = GetIndex(v2);

		_matrix[src][dest] = w;
		if(_isDirected = false) //说明是无向图
		{
			_matrix[dest][src] = w;
		}
	}

	//析构函数
	~GraphMatrix()
	{
		//先释放数据
		for(size_t i = 0; i<_v.size(); i++)
		{
			delete[] _matrix[i];
		}
		//后释放指针数组
		delete[] _matrix;
	}
private:
	vector<V> _v;     //顶点的集合
	W** _matrix;       //边上权重的集合
	bool _isDirected;  //是否是与有向图
};

void TestGraph()
{
	string gh1[] = {"北京","上海","天津","重庆","武汉"};
	GraphMatrix<string,int> gm(gh1,sizeof(gh1)/sizeof(gh1[0]));

	gm.AddEge("北京","上海",20);
	gm.AddEge("北京","天津",30);
	gm.AddEge("重庆","武汉",10);
	gm.AddEge("武汉","上海",25);
	gm.AddEge("天津","武汉",35);
}