#include<iostream>
#include<stack>
using namespace std; 


/***************���ڻ�����������ַ���**************/

//����ָ�뷨
//int PartSort1(int* a, int left,int right)
//{
//	//��������ȡ�з������Ż�,ֻ������������Ϳ���
//	//int key = GetMidIndex(a,left.right);
//	//swap(a[key],a[right]);
//
//	int key = right;
//	while(left < right)
//	{
//		while((left<right) && (a[left] <= a[key]))
//			left++;
//
//		while((left<right) && (a[right] >= a[key]))
//			right--;
//
//		if(a[left] > a[right])
//			std::swap(a[left],a[right]);
//		
//	}
//	std::swap(a[left],a[key]);
//	return left;
//}

//ǰ��ָ�뷨
//int PartSort2(int* a, int left,int right)
//{
//	int key = right;
//	int cur = left;
//	int pre = cur-1;
//	while(cur < right)
//	{
//		if((a[cur] < a[key]) && (++pre != cur))
//			swap(a[pre],a[cur]);
//		++cur;
//	}
//	swap(a[++pre],a[right]);
//	return pre;
//
//}
//
//
//�ڿӷ�
int PartSort3(int*a, int left,int right)
{
	//ע�⣺�ڿӷ�Ҫ�������Ҫ���ֵ���������±�
	int key = a[right];
	while(left < right)
	{
		while(left < right && a[left] <= key)
			left++;

		if(left<right)
			a[right] = a[left];

		while(left< right && a[right] >= key)
			right--;

		if(left<right)
			a[left]  =a[right];
		
	}
	a[left] = key;
	return left;
}

//
////�ǵݹ�ʵ�ֿ�������
//void QuickSortNonR(int* a,int left, int right)
//{
//	stack<int> s;
//	s.push(right);
//	s.push(left);
//	while(!s.empty())
//	{
//		int begin = s.top(); //��ʱȡ������left;
//		s.pop();
//		int end = s.top();  //��ʱȡ������right
//		s.pop();
//		
//		int div = PartSort(a,begin,end);
//		//begin, div+1
//		//div-1,end
//        if(begin < div1)
//		{
//			s.push(div-1);
//			s.push(begin);
//		}
//		if(end > div-1)
//		{
//			s.push(end);
//			s.push(div-1);
//
//		}
//
//	}
//
//}
//
//
//
******************���ڿ��ŵ��Ż�****************/
//1������ȡ�з�
//˵��������ȡ�Ĳ����м��������Ϊ���ȡ�����м�����Ļ���
//	    ��ô��Ҫ����Ų��Ԫ��
int GetMidIndex(int* a,int left,int right)
{
	int mid = left+ ((right-left)>>1);

	if(a[left] < a[mid])
	{
		if(a[right] > a[mid])
			return mid;

		else if(a[left] < a[right])
			return right;

		return left;
	}
	else
	{
		if(a[left]< a[right])
			return left;

		else if(a[mid] < a[right])
			return right;

		else
			return mid;
	}

}


////����������Ż�2��С�����Ż�
////����ֱ�Ӳ��뷨����
//void QuickSort(int* a,int left, int right)
//{
//	
//	if(right-left < 20)
//	{
//		Insert(a+left,a+right-1);
//	}
//	else{
//
//		if(left < right)
//		{
//			int div = PartSort(a,left,right);
//			QuickSort(a,left,div-1);
//			QuickSort(a,div+1,right);
//		}
//	}
//}

void QuickSort(int* a,int left, int right)
{
	if(left < right)
	{
		//int div = PartSort1(a,left,right);
		//int div = PartSort2(a,left,right);
		int div = PartSort3(a,left,right);

		QuickSort(a,left,div-1);
		QuickSort(a,div+1,right);
	}
}

void TestQuickSort()
{
	int i = 0;
	int a[10] = {2,0,4,9,3,6,8,7,1,5};
	int left = 0;
	int right = sizeof(a)/sizeof(a[0])-1;
	QuickSort(a,left,right);
	for(int i = 0; i<10; i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}