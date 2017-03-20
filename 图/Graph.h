#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include <assert.h>
#include<queue>
#include<algorithm>
#include"UnionFindSet.h"
template<class W>
struct LinKEdge
{
	W _weight;
	LinKEdge<W>* _next;
	size_t _src;
	size_t _dst;

	LinKEdge(size_t src = 0, size_t dst = 0, const W& w = W())
		:_src(src)
		,_dst(dst)
		,_weight(w)
		,_next(NULL)
	{}
};

template<class V, class W>
class GraphLink
{
	typedef LinKEdge<W> Edge;
public:
	
	GraphLink(V* vertexs, size_t n, const W& invalid = W(), bool isDirected = false)
		:_isDirected(isDirected)
	{
		_vertexs.resize(n);
		_vertexs.assign(vertexs, vertexs+n);

		_linkTables.resize(n, NULL);
	}
	size_t GetVertexIndex(const V& v)
	{
		for (size_t i = 0; i < _vertexs.size(); ++i)
		{
			if (_vertexs[i] == v)
			{
				return i;
			}
		}

		assert(false);
		return 0;
	}

	void _AddEdge(size_t src, size_t dst, const W& w)
	{
		// 头插
		LinKEdge<W>* edge = new Edge(src, dst, w);
		edge->_next = _linkTables[src];
		_linkTables[src] = edge;
	}

	void AddEdge(const V& v1, const V& v2, const W& w)
	{
		size_t src = GetVertexIndex(v1);
		size_t dst = GetVertexIndex(v2);

		_AddEdge(src, dst, w);
		if (_isDirected == false)
		{
			_AddEdge(dst, src, w);
		}
	}
//深度优先遍历
	void DFS(const V& src)
	{
		size_t index = GetVertexIndex(src);
		vector<bool> visited(_vertexs.size(),false);
		visited[index] = true;
		cout<<_vertexs[index]<<"->";
		_DFS(index,visited);
		
	}
	void _DFS(size_t src,vector<bool>& visited)
	{
		Edge* cur = _linkTables[src];
		while(cur)
		{
			size_t dst = cur->_dst;
			if(visited[dst] == false)
			{
				cout<<_vertexs[dst]<<"->"<<" ";
				visited[dst] = true;
				_DFS(dst,visited);
			}
			cur = cur->_next;
		}
	}
	
//广度优先遍历
	void BFS(const V& src)
	{
		size_t index = GetVertexIndex(src);
		vector<bool> visited(_vertexs.size(),false);
		queue<int> q;
		q.push(index);
		while(!q.empty())
		{
			size_t front = q.front();
			if(visited[front] == false)
			{
				cout<<_vertexs[front]<<"->";
				visited[front] = true;
				Edge* cur = _linkTables[front];
				while(cur)
				{
					size_t dst = cur->_dst;
					if(visited[dst] == false)
					{
						q.push(dst);
						visited[dst] = true;
						cout<<_vertexs[dst]<<"->";
					}
					cur = cur->_next;
				}
			}
			q.pop();
		}
	}


	//kruskal算法解生成最小树
	bool Kruscal(GraphLink<V,W>& mTree)
	{
		//先进行树的初始化
		mTree._isDirected = isDirected;
		mTree._linkTables.resize(_vertexs.size(),NULL);
		mTree._vertexs = _vertexs;

		//因为节点的比较是Edge*,因此要进行仿函数的重载
		struct Compare
		{
			bool operator()(Edge* l,Edge* r)
			{
				return l->_weight < r->_weight;
			}
		}
		
		//进行边的存储，按从小到大的顺序进行存储
		priority_queue<Edge*,vector<Edge*>,Compare> pq;
		for(int i = 0; i<_vertexs.size(); i++)
		{
			Edge* cur = _linkTables[i];
			//因为是无向图的存储，因此只存一半就可以
			while(cur)
			{
				if(cur->_src < cur->_dst)
				{
					pq.push(cur);
				}
				cur = cur->_next;
			}
		}

		//存储好后就进行边的选取，形成最小生成树
		int count = 0;
		UnionFindSet ufs(_vertexs.size());
		while(!pq.empty())
		{
			Edge* ret = pq.top();
			size_t src = ret->_src;
			size_t dest = ret->_dst;
			
			//如果添加的边不形成环的话
			if(ufs.IsUnion(src,dest) == false)
			{
				mTree.AddEdge(src,dest,ret->_weight);
				mTree.AddEdge(dest,src,ret->_weight);
				ufs.Union(src,dest);

				count++;
				if(count == _vertexs.size()-1)
					return true;
			}

		}
		return false;
	}

	//prim算法形成最小生成树
	bool Prim(GraphLink<V,W>& mTree)
	{
		//先进行树的初始化
		mTree._isDirected = isDirected;
		mTree._linkTables.resize(_vertexs.size(),NULL);
		mTree._vertexs = _vertexs;

		struct Compare
		{
			bool operator()(Edge* l,Edge* r)
			{
				return l->_weight < r->_weight;
			}
		}

		int count = 0;
		UnionFindSet ufs(_vertexs.size());
		while(!pq.empty())
		{
			priority_queue<Edge*,vector<Edge*>,Compare> pq;
			for(int i = 0; i<_vertexs.size(); i++)
			{
				Edge* cur = _linkTables[i];
				while(cur)
				{
					if(cur->_src < cur->_dst)
					{
						pq.push(cur);
					}
					cur = cur->_next;
				}
			}
			Edge* ret = pq.top();
			size_t src = ret->_src;
			size_t dest = ret->_dst;

			//如果添加的边不形成环的话
			if(ufs.IsUnion(src,dest) == false)
			{
				mTree.AddEdge(src,dest,ret->_weight);
				ufs.Union(src,dest);
				ret = _linkTable[dest];

				count++;
				if(count == _vertexs.size()-1)
					return true ;
			}

		}
	}

	//Prim算法中可以使用最小堆来进行边权重的存储
	bool Prim(GraphLink<V,W>& mTree)
	{
		//先进行树的初始化
		mTree._isDirected = isDirected;
		mTree._linkTables.resize(_vertexs.size(),NULL);
		mTree._vertexs = _vertexs;

		struct Compare
		{
			bool operator()(Edge* l,Edge* r)
			{
				return l->_weight < r->_weight;
			}
		}

		vector<Edge*> minHeap;
		Edge* cur = _linkTables[0];
		int count = 0;
		while(count < _vertexs.size()-1)
		{
			//将此点的所有边都放进堆中
			while(cur)
			{
				minHeap.push_back(cur);
				push_heap(cur.begin(),cur.end(),Compare());
				cur = cur->_next;
			}

			pop_heap(minHeap.begin(),minHeap.end(),Compare());   
			Node* minCur = minHeap.back();  
			minHeap.pop_back();  

			size_t src =minCur->_src;  
			size_t dst =minCur->_dst;  
			if (false == ufs.IsUnion(src,dst))  
			{  
				minTree._AddEdge(src,dst, minCur->_weight);  
				ufs.Union(src,dst);  
				cur = _tables[dst];  
				count++;
			}  
		}
	}
	//还可以用set实现



	
protected:
	vector<V> _vertexs;  // 顶点集合
	vector<Edge*> _linkTables; // 邻接表
	bool _isDirected;
};

void TestGraphLink()
{
	string city[] = {"西安", "安康", "延安", "渭南", "咸阳","北京","上海"};
	GraphLink<string, double> g1(city, sizeof(city)/sizeof(city[0]));
	g1.AddEdge("西安", "安康", 100.5);
	g1.AddEdge("西安", "上海", 19.5);
	g1.AddEdge("西安", "北京", 50.5);
	g1.AddEdge("延安", "渭南", 55);
	g1.AddEdge("延安", "北京", 25);
	g1.AddEdge("延安", "安康", 35);
	g1.AddEdge("咸阳", "北京", 15);
	g1.AddEdge("咸阳", "上海", 14);
	g1.AddEdge("咸阳", "渭南", 10);
	g1.AddEdge("上海", "西安", 4);
	g1.AddEdge("上海", "北京", 26);
	g1.AddEdge("上海", "咸阳", 28);
	g1.AddEdge("安康", "北京", 32);
	g1.AddEdge("安康", "西安", 5);
	g1.AddEdge("安康", "延安", 8);

	g1.Kruscal(GraphLink<string,double> g1);
	g1.DFS("西安");
	cout<<endl;
	g1.BFS("西安");
}