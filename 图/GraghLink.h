#include<iostream>
using namespace std; 
#include<vector>
#include<assert.h>
#include<string>
//用邻接表的方式表示图
template<class W>
struct GraphLinkNode
{
	W _weight;       //权重
	GraphLinkNode<W*> _next;  //下一个节点
	size_t _src;      
	size_t _dest;
	GraphLinkNode(size_t src,size_t dest,const W& weight = W())
		:_weight(weight)
		,_next(NULL)
		,_src(src)
		,_dest(dest)
	{}
};

template<class V,class W>
class GraphLink
{
	typedef GraphLinkNode<W> Node;
public:
	//构造函数
	GraphLink(V* v,size_t n,bool isDirected = false)
		:_isDirected(isDirected)
	{
		_v.resize(n);   //是要赋成不同的值，所以不用resize;
		_v.assign(v,v+n);
		_linktable.resize(n,NULL);
	}

	//给定一个顶点得到它对应的下标
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

	//如何添加一条边
	void AddEdge(const V& v1,const V& v2,const W& w)
	{
		size_t src = GetIndex(v1);
		size_t dest = GetIndex(v2);
		_AddEdge(src,dest,w);
		if(_isDirected == false)
		{
			_AddEdge(dest,src,w);
		}
		
	}
	
protected:
	void _AddEdge(size_t src,size_t dest,const W& w)
	{
		Node* edge = new Node(src,dest,w);
		edge->_next = _linktable[src];
		_linktable[src] = edge;

	}
private:
	vector<V> _v;        //顶点
	vector<Node*> _linktable;   //邻接表可以用指针数组来进行表示
	bool _isDirected;   //是否是有向图
};

void TestGraph()
{
	string gh1[] = {"北京","上海","天津","重庆","武汉"};

	GraphLink<string,int> gm(gh1,sizeof(gh1)/sizeof(gh1[0]));

	gm.AddEdge("北京","上海",20);
	gm.AddEdge("北京","天津",30);
	gm.AddEdge("重庆","武汉",10);
	gm.AddEdge("武汉","上海",25);
	gm.AddEdge("天津","武汉",35);

}