#include<iostream>
#include<assert.h>
using namespace std;
//广义表的类型：三种：
enum Type
{
	HEAD,
	VALUE,
	SUB
};
struct GeneralListNode
{
	GeneralListNode(const Type& type,char value = 0)
		:_type(type)
		,_next(NULL)
		,_sublink(NULL)
	{
		_value = value;   //注意这块直接赋值
	}
	Type _type;
	GeneralListNode* _next;
	union
	{
		char _value;
		GeneralListNode* _sublink;
	};
};
class GeneralList
{
public:
	typedef GeneralListNode Node;
public:
	//构造函数
	GeneralList()
		:_head(NULL)
	{}
	GeneralList(const char* str)
		:_head(NULL)
	{
		_head = Creat(str);	
	}
	Node* Creat(const char*&str)   //注意传引用
	{
		assert(str&&*str == '(');
		Node* head = new Node(HEAD);//先定义一个只有头节点的
		Node* cur = head;
		str++;
		//接下来分情况：有值得或者是有子表的，或者其他
		while(*str)
		{
			if((*str >= '0' && *str<='9')||
				(*str>='a' && *str<='z')||
				(*str>='A' && *str<='Z'))
			{
				Node* ret = new Node(VALUE,*str);
				cur->_next = ret;
				cur = cur->_next;
				str++;
			}
			else if(*str == '(')
			{
				Node* ret = new Node(SUB);
				cur->_next = ret;
				//str++;
				ret->_sublink = Creat(str);
				cur = cur->_next;
			}
			else if(*str == ')')  //已经到广义表的最后了
			{
				str++;
				return head;
			}
			else
			{
				++str;
			}
		}
		return head;
	}
	//拷贝构造函数
	GeneralList(const GeneralList& g)
	{
		_head = Copy(g._head);
	}
	Node* Copy(Node* head)
	{
		assert(head&&head->_type==HEAD);
		Node* cur = head;  //原来的
		Node* tail = new Node(HEAD);  //指向子表
		Node* newhead = tail;
		while(cur)
		{
			if(cur->_type == VALUE)
			{
				Node* ret = new Node(cur->_type,cur->_value);
				tail->_next = ret;
				tail = tail->_next;
				cur = cur->_next;
			}
			else if(cur->_type == SUB)
			{
				Node* ret = new Node(cur->_type);
				tail->_next = ret;
				tail = tail->_next;
				tail->_sublink = Copy(cur->_sublink);
				cur = cur->_next;
			}
			else
				cur = cur->_next;
		}
		return newhead;
	}
	//赋值运算符重载
	GeneralList& operator=(const GeneralList& g)
	{
		//普通的传统写法
		if(this != &g)
		{
			Node* temp = Copy(g._head);
			if(_head!=NULL)
				Destory(_head);
			_head = temp;
		}
		return *this;
		//现在的简洁写法:
		/*:写法一：
		Node* Assign temp(g);
		std::swap(_head,temp._head);
		return *this;

		写法二：
		Node* Assign(GeneralList g)
		{
			swap(_head,g._head);
			return *this;
		}
		写法三：
		Node* Assign(const GeneralList& g)
		{
			Assign temp(g._head);
			swap(_head,temp._head);
			return *this;
		}
		*/
	
	}	
	//析构函数
	~GeneralList()
	{
		if(_head)
		{
			Destory(_head);
		}
		_head = NULL;
	}
	void Destory(Node* head)
	{
		assert(head&&head->_type==HEAD);
		Node* cur = head;
		while(cur)
		{
			if(cur->_type == SUB)
			{
				Destory(cur->_sublink);
			}
			Node* del = cur;
			cur = cur->_next;
			delete del;
		}
	}
	//求广义表的元素的个数
	size_t Size()
	{
		return _Size(_head);
	}
	size_t _Size(Node* head)
	{
		assert(head&&head->_type==HEAD);
		size_t count = 0;
		Node* cur = head;
		while(cur)
		{
			if(cur->_type == VALUE)
			{
				count++;
			}
			if(cur->_type == SUB)
			{
				count += _Size(cur->_sublink);
			}
			cur = cur->_next;
		}
		return count;
	}
	//求广义表的深度
	size_t Depth()
	{
		return _Depth(_head);
	}
	size_t _Depth(Node* head)
	{
		assert(head&&head->_type==HEAD);
		size_t maxSize = 1;
		size_t depth = 1;
		Node* cur = head;
		while(cur)
		{
			if(cur->_type == SUB)
			{
				if(depth+1 > maxSize)
				{
					maxSize = depth+1;
				}
				depth = _Depth(cur->_sublink);
			}
			cur = cur->_next;
		}
		return maxSize;
	}
	//打印函数
	void Print()
	{
		_Print(_head);
		cout<<endl;
	}
	//(a,b,(c,d))
	void _Print(Node* head)
	{
		assert(head&&head->_type==HEAD);
		Node* cur = head;
		cout<<'(';
		while(cur)	
		{
			if(cur->_type == HEAD)
			{
				cur = cur->_next;
			}
			else if(cur->_type == VALUE)
			{
				cout<<cur->_value;
				if(cur->_next)
				{
					cout<<',';
					cur = cur->_next;
				}
				else
				{
					return ;
				}
			}
			else if(cur->_type == SUB)
			{
				_Print(cur->_sublink);
				cout<<')';
				if(cur->_next)
				{
					cout<<',';
					cur = cur->_next;
				}
				else
				{
					break;
				}
			}
		}
			cout<<')';
			
	}
protected:
	Node* _head;
};

/**********测试函数****************/
void Test()
{
	/*GeneralList g1("(a,b)");
	g1.Print();*/

	GeneralList g1("(a,b,(c,d))");
	cout<<g1.Size()<<endl;
	cout<<g1.Depth()<<endl;
	g1.Print();

	GeneralList g2(g1);
	g2.Print();
	GeneralList g3;
	g3 = g2;
	g3.Print();
	

}
