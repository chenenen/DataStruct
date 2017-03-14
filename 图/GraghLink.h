#include<iostream>
using namespace std; 
#include<vector>
#include<assert.h>
#include<string>
//���ڽӱ�ķ�ʽ��ʾͼ
template<class W>
struct GraphLinkNode
{
	W _weight;       //Ȩ��
	GraphLinkNode<W*> _next;  //��һ���ڵ�
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
	//���캯��
	GraphLink(V* v,size_t n,bool isDirected = false)
		:_isDirected(isDirected)
	{
		_v.resize(n);   //��Ҫ���ɲ�ͬ��ֵ�����Բ���resize;
		_v.assign(v,v+n);
		_linktable.resize(n,NULL);
	}

	//����һ������õ�����Ӧ���±�
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

	//������һ����
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
	vector<V> _v;        //����
	vector<Node*> _linktable;   //�ڽӱ������ָ�����������б�ʾ
	bool _isDirected;   //�Ƿ�������ͼ
};

void TestGraph()
{
	string gh1[] = {"����","�Ϻ�","���","����","�人"};

	GraphLink<string,int> gm(gh1,sizeof(gh1)/sizeof(gh1[0]));

	gm.AddEdge("����","�Ϻ�",20);
	gm.AddEdge("����","���",30);
	gm.AddEdge("����","�人",10);
	gm.AddEdge("�人","�Ϻ�",25);
	gm.AddEdge("���","�人",35);

}