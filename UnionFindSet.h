#include<iostream>
#include<vector>
using namespace std;

class UnionFindSet
{
public:
	//构造函数
	UnionFindSet(size_t n)
	{
		_ufs.resize(n,-1);
	}
	//查找当前数的根
	int FindRoot(int x)
	{
		while(_ufs[x] > 0)
		{
			x = _ufs[x];
		}
		return x;
	}
	//合并并查集
	void Union(int x1,int x2)
	{
		//首先得到两个数的根（因为进行合并的时候是根的合并）
		int root1 = FindRoot(x1);
		int root2 = FindRoot(x2);
		
		//进行合并，将其中一个根对应的数据加到另一个上，
		//接着此根的数据变为另一个根
		if(root1 != root2)
		{
			_ufs[root1] += _ufs[root2];
			_ufs[root2] = root1;
		}

	}

	//求有多少个根
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
	UnionFindSet u(n+1);     //多申请一个空间
	for(int i = 0; i<m; i++)
	{
		u.Union(r[i][0],r[i][1]);
	}
	return u.CountRoot()-1;       //这块要减1    
}

//测试函数
void TestUnionFindSet()
{
	int n = 5;  //共有n个人
	int m = 3;  //有m对好友关系
	int r[][2]= {{1,2},{2,3},{4,5}};  //朋友圈
	cout<<Friends(n,m,r)<<endl;
}
 