//˵��set�ĵײ�ʵ���Ǻ�������ṹ��k���͵�
#include<iostream>
using namespace std;
#include<set>
typedef set<int,greater<int>> setsort;
void TestSet()
{
	//����Ĳ���
	//1��ֱ�Ӳ���һ��ֵ
	set<int> s1;
	s1.insert(1);
	s1.insert(2);
	s1.insert(3);
	s1.insert(4);
	s1.insert(5);

	//2�����ض���λ�ý��в���
	/*s1.insert(s1.begin(),10);
	s1.insert(s1.begin(),5);
	s1.insert(s1.begin(),7);
	s1.insert(s1.begin(),9);*/

	//3������һ������
	//s1.insert (s1.begin(),s1.end());

		
	//ɾ���Ĳ���
	//1��ֱ��ɾ��ֵ
	//˵����ɾ�����ֵ��ʱ�����������ԭ���Ĳ���������ʱ�����ᷢ������
	/*s1.erase(4);
	s1.erase(1);
	s1.erase(6);*/

	//2��ɾ��һ���ض�λ�õ�ֵ
	//˵���������ɾ��һ��λ���ϵ����Ļ������û��������Ļ���ɾ���Ļ�
	//      �ͻ����
	//set<int>::iterator pos = s1.find(6);
	//s1.erase(pos);

	//3��ɾ��һ�ε���������
	//s1.erase(++s1.begin(),--s1.end());
	
	set<int>::iterator it1 = s1.begin();
	while(it1 != s1.end())
	{
		cout<<*it1<<" ";
		it1++;
	}
	cout<<endl;

	//cout�ж�һ��ֵ�Ƿ���ڣ�������ڵĻ�����1�������ڵĻ�����0
	//cout<<s1.count(1)<<endl;

	//emplace:c++11������
	//˵�������ڲ���һ��Ԫ�أ���insert��Ч�ʸ�һЩ
	//      insert�����ʱ�򷵻����Ƚ��й���һ����ʱ����
	//		Ȼ��ͨ�������ʱ�����ٽ��п�������
	//		��emplace��ֱ�Ӿͽ��еĹ��죬Ч�ʸ���һЩ
	//set<string> s2;
	//s2.emplace("hello");
	//auto ret = s2.emplate("hello");
	//if(!ret.second)
	//	cout<<"hello �Ѿ�����"<<endl;

	//����
	//˵����set������Ĭ���������

	//Ӧ��С�᣺
	1�����Խ��е��ʵ�ƴд���
	2����Ϊset�Ĳ����Ƿ�����ģ��й��˵����ã�������ǿ���
	   ʵ������set��ʵ������

}