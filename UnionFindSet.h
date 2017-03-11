#include<iostream>
#include<vector>
using namespace std;

class UnionFindSet
{
public:
	//���캯��
	UnionFindSet(size_t n)
	{
		_ufs.resize(n,-1);
	}
	//���ҵ�ǰ���ĸ�
	int FindRoot(int x)
	{
		while(_ufs[x] > 0)
		{
			x = _ufs[x];
		}
		return x;
	}
	//�ϲ����鼯
	void Union(int x1,int x2)
	{
		//���ȵõ��������ĸ�����Ϊ���кϲ���ʱ���Ǹ��ĺϲ���
		int root1 = FindRoot(x1);
		int root2 = FindRoot(x2);
		
		//���кϲ���������һ������Ӧ�����ݼӵ���һ���ϣ�
		//���Ŵ˸������ݱ�Ϊ��һ����
		if(root1 != root2)
		{
			_ufs[root1] += _ufs[root2];
			_ufs[root2] = root1;
		}

	}

	//���ж��ٸ���
	int CountRoot()
	{
		int count = 0;
		for(int i = 0; i<_ufs.size(); i++)
		{
			if(_ufs[i] < 0)
			{
				count++;
			}
		}
		return count;
	}

	
private:
	vector<int> _ufs;

};

int Friends(int n,int m,int r[][2])
{
	UnionFindSet u(n+1);     //������һ���ռ�
	for(int i = 0; i<m; i++)
	{
		u.Union(r[i][0],r[i][1]);
	}
	return u.CountRoot()-1;       //���Ҫ��1    
}

//���Ժ���
void TestUnionFindSet()
{
	int n = 5;  //����n����
	int m = 3;  //��m�Ժ��ѹ�ϵ
	int r[][2]= {{1,2},{2,3},{4,5}};  //����Ȧ
	cout<<Friends(n,m,r)<<endl;
}
 