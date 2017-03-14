#include<iostream>
using namespace std; 
#include<vector>
#include<assert.h>
#include<string>
//˵�������ڽӾ���ķ�ʽ��ʾͼ
template<class V,class W>
class GraphMatrix
{
public:
	//���캯��
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

	//����һ�����㣬��εõ����������±�
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
	//��μ�һ����
	void AddEge(const V& v1, const V& v2, const W& w)
	{
		size_t src = GetIndex(v1);
		size_t dest = GetIndex(v2);

		_matrix[src][dest] = w;
		if(_isDirected = false) //˵��������ͼ
		{
			_matrix[dest][src] = w;
		}
	}

	//��������
	~GraphMatrix()
	{
		//���ͷ�����
		for(size_t i = 0; i<_v.size(); i++)
		{
			delete[] _matrix[i];
		}
		//���ͷ�ָ������
		delete[] _matrix;
	}
private:
	vector<V> _v;     //����ļ���
	W** _matrix;       //����Ȩ�صļ���
	bool _isDirected;  //�Ƿ���������ͼ
};

void TestGraph()
{
	string gh1[] = {"����","�Ϻ�","���","����","�人"};
	GraphMatrix<string,int> gm(gh1,sizeof(gh1)/sizeof(gh1[0]));

	gm.AddEge("����","�Ϻ�",20);
	gm.AddEge("����","���",30);
	gm.AddEge("����","�人",10);
	gm.AddEge("�人","�Ϻ�",25);
	gm.AddEge("���","�人",35);
}