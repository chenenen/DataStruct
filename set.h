//说明set的底层实现是红黑树，结构是k类型的
#include<iostream>
using namespace std;
#include<set>
typedef set<int,greater<int>> setsort;
void TestSet()
{
	//插入的测试
	//1、直接插入一个值
	set<int> s1;
	s1.insert(1);
	s1.insert(2);
	s1.insert(3);
	s1.insert(4);
	s1.insert(5);

	//2、在特定的位置进行插入
	/*s1.insert(s1.begin(),10);
	s1.insert(s1.begin(),5);
	s1.insert(s1.begin(),7);
	s1.insert(s1.begin(),9);*/

	//3、插入一段区间
	//s1.insert (s1.begin(),s1.end());

		
	//删除的测试
	//1、直接删除值
	//说明：删除这个值得时候，如果不在你原本的插入数据中时，不会发生崩溃
	/*s1.erase(4);
	s1.erase(1);
	s1.erase(6);*/

	//2、删除一个特定位置的值
	//说明：如果是删除一个位置上的数的话，如果没有这个数的话，删除的话
	//      就会崩溃
	//set<int>::iterator pos = s1.find(6);
	//s1.erase(pos);

	//3、删除一段迭代器区间
	//s1.erase(++s1.begin(),--s1.end());
	
	set<int>::iterator it1 = s1.begin();
	while(it1 != s1.end())
	{
		cout<<*it1<<" ";
		it1++;
	}
	cout<<endl;

	//cout判断一个值是否存在，如果存在的话返回1，不存在的话返回0
	//cout<<s1.count(1)<<endl;

	//emplace:c++11新特性
	//说明：用于插入一个元素，比insert的效率高一些
	//      insert插入的时候返回是先进行构造一个临时对象，
	//		然后通过这个临时对象再进行拷贝构造
	//		而emplace是直接就进行的构造，效率更高一些
	//set<string> s2;
	//s2.emplace("hello");
	//auto ret = s2.emplate("hello");
	//if(!ret.second)
	//	cout<<"hello 已经存在"<<endl;

	//排序
	//说明：set的排序默认是升序的

	//应用小结：
	1）可以进行单词的拼写检查
	2）因为set的插入是仿冗余的，有过滤的作用，因此我们可以
	   实现利用set来实现爬虫

}