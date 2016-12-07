#include<iostream>
#include<stack>
using namespace std;
enum Type
{
	OP_SYMBOL,  //符号，记录传进来的操作符
	OP_NUM,      //操作数
	//操作符
	ADD, //注意全角符号
	SUB,
	MUL,
	DIV,
};
struct Cell
{
	Type _type;     //每个传进来的单元的类型
	int _value;    //是操作数，就是数值
};
int CountRPN(Cell* rpn,size_t n)
{
	stack<int> s;
	for(size_t i= 0; i<n; i++)
	{
		//先判断传进来的是操作符还是操作数
		//是操作数压栈
		if(OP_NUM == rpn[i]._type)
		{
			s.push(rpn[i]._value);
		}
		//是操作符出栈
		if(OP_SYMBOL == rpn[i]._type)
		{
			int right = s.top();
			s.pop();
			int left = s.top();
			s.pop();
			//是操作符，就进行四则运算
			switch(rpn[i]._value)
			{
				case ADD:
					s.push(left+right);
					break;
				case SUB:
					s.push(left-right);
					break;
				case MUL:
					s.push(right*left);
					break;
				case DIV:
					if(left == 0)
					{
						throw std::invalid_argument("参数错误！");
					}
					s.push(right/left);
					break;
				default:
					throw std::invalid_argument("参数异常");
					break;
			}
		}
		
	}
	return s.top();
}
void TestRPN()
{//12-3*4-5+2 = -3
	//后缀表达式：12 3 4 * -5 -
	Cell rpn[] = {
		{OP_NUM,12},
		{OP_NUM,3},
		{OP_NUM,4},
		{OP_SYMBOL,MUL},
		{OP_SYMBOL,SUB},
		{OP_NUM,5},	
		{OP_SYMBOL,SUB},
		{OP_NUM,2},
		{OP_SYMBOL,ADD},
		};
		try
	{
		cout<<CountRPN(rpn, sizeof(rpn)/sizeof(rpn[0]))<<endl;
	}
	
	catch(exception&e)
	{
		e.what();
		cout<<"err"<<endl;	
	}
	
}


