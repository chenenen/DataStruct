#include<iostream>
#include<assert.h>
#include<stack>
using namespace std;
#define N 10
//const size_t N = 10;

//�Թ������ߵ�λ�ñ�ʾ
struct Pos
{
   /* size_t*/ int _row;  //����λ�õ���
	/*sizt_t*/int _col;  //����λ�õ���
};

//��ȡ�Թ�
void GetMaze(int* maze,size_t n)
{
	FILE* fp = fopen("2.txt","r");  //��ͨ�����·���򿪴洢�Թ���ͼ���ı�
	assert(fp);       //���ı��Ƿ�ɹ�
	for(size_t i = 0; i<n; i++)
	{
		for(size_t j = 0; j<n;)
		{
			int ret = fgetc(fp);
			if((ret == '0')|| (ret == '1'))
			{
				maze[i*n+j] = ret-'0';      //ע��򿪵����ı�Ҫת���ɶ����Ķ�������ʽ
				j++;
			}
			//����Թ���ͼ������n*n�ģ���ô�����ѭ���ͻ��Ϊ��ѭ��
			if(ret == EOF)
			{
				cout<<"����"<<endl;
			}
		}
	}
}
//����λ���Ƿ����ͨ
bool CheckIsAccess(int* maze,size_t n,Pos pos)
{
	//�������λ�õúϷ����������pos���λ���Ƿ�Ϊ0
	if(pos._row>=0 && pos._row<n &&
		pos._col>=0 && pos._col<n &&
		maze[pos._row*n+pos._col] == 0)
	{
		return true;
	}
	return false;
}
//����Թ�·��
void GetMazePath_r(int* maze,size_t n,Pos entry,stack<Pos>& path)
{
	assert(maze);
	path.push(entry);
	Pos cur;    
	Pos next;
    cur = entry;
	maze[cur._row*n+cur._col] = 2;   //���߹������λ�ý��б��
	next = cur;
	if(next._row == n-1)
	{
		return ;   //�ҵ���һ��ͨ·
	}
	//��ʼ���������ҽ���̽��
	//���ϵ�̽��
	next = cur;
	next._row -= 1;
	//���·�Ƿ����ͨ
	if(CheckIsAccess(maze,n,next))
	{
		GetMazePath_r(maze,n,next,path);
	}
	//���µ�̽��
	next = cur;
	next._row += 1;
	//���·�Ƿ����ͨ
	if(CheckIsAccess(maze,n,next))
	{
		GetMazePath_r(maze,n,next,path);
	}
	//�����̽��
	next = cur;
	next._col -= 1;
	//���·�Ƿ����ͨ
	if(CheckIsAccess(maze,n,next))
	{
		GetMazePath_r(maze,n,next,path);
	}
	//���ҵ�̽��
	next = cur;
	next._col += 1;
	//���·�Ƿ����ͨ
	if(CheckIsAccess(maze,n,next))
	{
		GetMazePath_r(maze,n,next,path);
	}
	//�����λ�ã�˵���ĸ������߲�ͨ�����л���
	path.pop();  
}   


//��ӡ�Թ�
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
