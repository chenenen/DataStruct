#include<iostream>
#include<stack>
using namespace std;
enum Type
{
	OP_SYMBOL,  //���ţ���¼�������Ĳ�����
	OP_NUM,      //������
	//������
	ADD, //ע��ȫ�Ƿ���
	SUB,
	MUL,
	DIV,
};
struct Cell
{
	Type _type;     //ÿ���������ĵ�Ԫ������
	int _value;    //�ǲ�������������ֵ
};
int CountRPN(Cell* rpn,size_t n)
{
	stack<int> s;
	for(size_t i= 0; i<n; i++)
	{
		//���жϴ��������ǲ��������ǲ�����
		//�ǲ�����ѹջ
		if(OP_NUM == rpn[i]._type)
		{
			s.push(rpn[i]._value);
		}
		//�ǲ�������ջ
		if(OP_SYMBOL == rpn[i]._type)
		{
			int right = s.top();
			s.pop();
			int left = s.top();
			s.pop();
			//�ǲ��������ͽ�����������
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
						throw std::invalid_argument("��������");
					}
					s.push(right/left);
					break;
				default:
					throw std::invalid_argument("�����쳣");
					break;
			}
		}
		
	}
	return s.top();
}
void TestRPN()
{//12-3*4-5+2 = -3
	//��׺���ʽ��12 3 4 * -5 -
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


