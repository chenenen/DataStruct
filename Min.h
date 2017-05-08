#include<iostream>
#include<stack>
using namespace std;
template<class T>
class MinStack
{
public:
	MinStack(){}

	void Push(const T& x)
	{
		s1.push(x);
		if (min.empty() || x < min.top())
			min.push(x);
		else
			min.push(min.top());
	}

	void Pop()
	{
		if (!min.empty() && !s1.empty())
		{
			s1.pop();
			min.pop();
		}
	}

	const T& Min()const
	{
		return min.top();
	}
private:
	stack<T> s1;
	stack<T> min;
};

void Test()
{
	MinStack<int> ms;
	ms.Push(3);
	ms.Push(4);
	ms.Push(2);
	ms.Push(1);

	ms.Pop();
	ms.Pop();

	ms.Push(0);

}