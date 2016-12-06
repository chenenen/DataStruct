#include<iostream>
#include<assert.h>
#include<stack>
using namespace std;
#define N 10
//const size_t N = 10;

//迷宫中所走的位置表示
struct Pos
{
   /* size_t*/ int _row;  //所在位置的行
	/*sizt_t*/int _col;  //所在位置的列
};

//获取迷宫
void GetMaze(int* maze,size_t n)
{
	FILE* fp = fopen("1.txt","r");  //先通过相对路径打开存储迷宫地图的文本
	assert(fp);       //打开文本是否成功
	for(size_t i = 0; i<n; i++)
	{
		for(size_t j = 0; j<n;)
		{
			int ret = fgetc(fp);
			if((ret == '0')|| (ret == '1'))
			{
				maze[i*n+j] = ret-'0';      //注意打开的是文本要转化成读出的二进制形式
				j++;
			}
			//如果迷宫地图本身不是n*n的，那么上面的循环就会成为死循环
			if(ret == EOF)
			{
				cout<<"出错！"<<endl;
			}
		}
	}
}
//检查此位置是否可以通
bool CheckIsAccess(int* maze,size_t n,Pos pos)
{
	//首先这个位置得合法，其次再是pos这个位置是否为0
	if(pos._row>=0 && pos._row<n &&
		pos._col>=0 && pos._col<n &&
		maze[pos._row*n+pos._col] == 0)
	{
		return true;
	}
	return false;
}
//求解迷宫路径
bool GetMazePath(int* maze,size_t n,Pos entry,stack<Pos>& path)
{
	assert(maze);
	path.push(entry);
	Pos cur;    
	Pos next;
	while(!path.empty())  //当栈不为空的时候，才能进行路径的寻找
	{
		cur = path.top(); 
		maze[cur._row*n+cur._col] = 2;   //把走过的这个位置进行标记
		next = cur;  //在每次进行判断之后，要将next进行重置    
		if(next._row == n-1)
		{
			return true;   //找到了一条通路
		}
		//开始对上下左右进行探测
		//对上的探测
		next._row -= 1;
		//检查路是否可以通
		if(CheckIsAccess(maze,n,next))
		{
			path.push(next);
			continue;
		}
		//对下的探测
		next = cur;
		next._row += 1;
		//检查路是否可以通
		if(CheckIsAccess(maze,n,next))
		{
			path.push(next);
			continue;
		}
		//对左的探测
		next = cur;
		next._col -= 1;
		//检查路是否可以通
		if(CheckIsAccess(maze,n,next))
		{
			path.push(next);
			continue;
		}
		//对右的探测
		next = cur;
		next._col += 1;
		//检查路是否可以通
		if(CheckIsAccess(maze,n,next))
		{
			path.push(next);
			continue;
		}
		//到这个位置，说明四个方向都走不通，进行回溯
		path.pop();    //直接出栈，即前一个位置，再次上去进行探测
	}

	return false;  //栈为空，没有找到通路     
}


//打印迷宫
void Print(int* maze, size_t n)
{
	for(size_t i = 0; i<n; i++)
	{
		for(size_t j = 0; j<n; j++)
		{
			cout<<maze[i*n+j];
		}
		cout<<endl;
	}
}
