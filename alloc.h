#include<iostream>
#include<vector>
#include<stdarg.h>
using namespace std;
/********************Trace**************************/
#define __DEBUG__

static string GetFileName(const string& path)
{
	char ch='/';
#ifdef _WIN32
	ch='\\';
#endif
	size_t pos = path.rfind(ch);
	if(pos==string::npos)
		return path;
	else
		return path.substr(pos+ 1);
}//

inline static void __trace_debug(const char* function,
								 const char* filename,int line,char* format, ...)
{
#ifdef __DEBUG__
	//输出调用函数的信息
	fprintf(stdout,"【 %s:%d】 %s",GetFileName(filename).c_str(),line,function);

	//输出用户打的trace信息
	va_list args;
	va_start(args,format);
	vfprintf(stdout,format,args);
	va_end(args);
#endif
} 
#define __TRACE_DEBUG(...) \
	__trace_debug(__FUNCTION__,__FILE__,__LINE__,__VA_ARGS__);






/***************************一级空间配置器*********************/
template<int inst>
class _MallocAllocTemplate
{
public:
	
	typedef void(*HANDLER)();
	static HANDLER _mallocAllocOOmHandler;
public:
	//申请空间
	static void* Allocate(size_t n)
	{
		__TRACE_DEBUG("一级空间配置器申请%uBytes\n", n);
		void* result = malloc(n);
		if(result == 0)
			result = OOm_Malloc(n);
		return result;
	}

	static void * OOm_Malloc(size_t n)
	{
		void* result;

		//此处设置为死循环:不断的调用内存不足处理机制，期望着在某一次能够成功
		while(1)
		{
			//类似与c++中的new_handler机制：是一种客端指定的处理例程。
			//可能是内存释放函数，将地址给_mallocAllocOOmHandler

			//失败了，抛出异常
				if(NULL == _mallocAllocOOmHandler)
				{
					throw std::bad_alloc;
				}
			//再次进行申请
				else
				{
					result = malloc(n);
				}
				if(result)
					return result;
		}
	}

	//空间的释放
	static void Deallocate(void* p)
	{
		__TRACE_DEBUG("一级空间配置器释放0x%p,%uBytes\n", p,n);
		free(p);
	}

	//函数指针指向具体的一个函数，在这个函数中处理异常
	//SetMallocHandler将HANDLER 指向一个函数，在这个函数中处理异常，
	//如果HANDLER 为空，那么这个函数就没有执行，就会抛异常。
	static HANDLER SetMallocHandler(HANDLER f)
	{
		HANDLER old =  _mallocAllocOOmHandler;
		_mallocAllocOOmHandler = f;
		return (old);
	}
};

template<int inst>
typename _MallocAllocTemplate<inst>
	::HANDLER _MallocAllocTemplate<inst>
	::_mallocAllocOOmHandler=0;


/********************二级空间配置器***********************/
template<bool threads,int inst>
class _DefaultAllocTemplate
{
protected:
	enum {_ALIGN = 8};  //自由链表中的基准值
	enum {_MAX_BYTES = 128};   //自由链表中最大的值
	enum {_NFREELISTS = _MAX_BYTES/_ALIGN};  //可以对应多少个下标（指针数组）

	//自由链表中节点的定义
	union obj
	{
		obj* _freeListLink; //指向下一个内存块对象的指针
		char clientData[1]; 
	};

	//自由链表其实就是一个指针数组（+下面挂接内存块）
	static obj* freeList[_NFREELISTS];

	//大块内存分配的时候的状态
	static char* startFree;   //内存池的开始
	static char* endFree;     //内存池的结束
	static size_t heapSize;   //得到的总内存大小

/////////开始进行内存的分配处理机制///////////
public:
	//先进行下标的计算，看要在自由链表的那个位置进行内存的申请或者挂接
	//说明:这里在计算下标的时候，很巧妙
	//计算的时候是计算到下一个范围中，然后进行下标-1，这样就不用对没有
	//内存对齐的进行分类处理了
	static  size_t FREELIST_INDEX(size_t bytes)
	{
        return (((bytes) + _ALIGN-1)/_ALIGN - 1);
	}

	//这个函数实际上就是用于内存对齐
	//将一个数分成两部分，前一部分满足对齐，将后一部分去除掉
	//举个例子：7  8
	//
	//   16  8  4  2  1
	// 7: 0  0  1  1  1
	// 8: 0  1  1  1  1
	// (7+8-1)& ~(7)
	// 14:0  1  1  1  0
	// ~7:1  1  0  0  0
//结果：  0  1  0  0  0
	//可以看到以基准值为基准线，将它对齐到基准值了
	static size_t ROUND_UP(size_t bytes)
	{
		return (((bytes) + _ALIGN-1) & ~(_ALIGN-1));
	}

public:

	//大块内存的申请
	//这块需要注意的是返回值是char* ，不然不知如何进行切分
	static char* ChunkAlloc(size_t size, /*int*/size_t & nobjs)
	{
		size_t bytesToGet = 0;
		char* result;
		size_t totalBytes = size*nobjs;//需要的内存总数
		size_t leftBytes = endFree-startFree; //内存池剩余的内存

		__TRACE_DEBUG("内存池剩余%ubytes,需要申请%uBytes\n",
					leftBytes,totalBytes);
		//分三种情况

		//1、当内存池中的内存足够你需求的内存时
		if(leftBytes > totalBytes)
		{
			__TRACE_DEBUG("内存有足够%u个对象大小内存\n", nobjs);
			result = startFree;
			startFree += totalBytes;
			return result;
		}
		//2、当内存池中的内存大于1个但是不够你需求的时候
		else if(leftBytes > 0)
		{
			//有多少就申请多少
			nobjs = totalBytes/size;
			totalBytes = nobjs*size;

			__TRACE_DEBUG("内存只能够分配%u个对象大小内存\n", nobjs);
			startFree += totalBytes;
			return result;
		}
		//3、内存池中连一个size的大小都不够，这时就要去系统中进行申请
		else
		{
			//去系统中申请这么大的内存
			bytesToGet = 2 * totalBytes + ROUND_UP(heapSize >> 4);
			//但是内存池中可能还有内存,先将这个内存放到对应的内存块中
			if(leftBytes >0)
			{
				__TRACE_DEBUG("将剩余的%uBytes小片内存挂到自由链表上\n", leftBytes);

				size_t index = FREELIST_INDEX(leftBytes);
				((obj*)startFree)->_freeListLink = freeList[index];
				freeList[index] = (obj*)startFree;
			}
			startFree = (char*)malloc(bytesToGet);
			//如果在系统中申请失败了,那么就到更大的自由链表中去申请
			if(startFree == 0)
			{
				//__TRACE_DEBUG("到更大的自由链表上申请内存\n");

				for(int i = size; i<_MAX_BYTES; i+= _ALIGN)
				{
					size_t index = FREELIST_INDEX(leftBytes);
					//如果申请成功了
					if(freeList[index])
					{
						__TRACE_DEBUG("到更大的自由链表上申请内存\n");

						startFree = (char*)freeList[index];
						freeList[index] = ((obj*)startFree)->_freeListLink;
						endFree = startFree+i;
						return ChunkAlloc(size,nobjs);
					}
				}
			
			}
			endFree = NULL;//防止异常

			//到这块系统内存都吃紧了，也就是山穷水尽了，就尝试这去
			//调用一级空间配置器
			startFree = (char*)_MallocAllocTemplate<0>::Allocate(bytesToGet);
		}

		//从系统中获得的总字节数，可以用于下次调节
		heapSize += bytesToGet;
		endFree = startFree + bytesToGet;
		return ChunkAlloc(size,nobjs);
		
	}
	
	//将申请的内存切分挂接到自由链表中
	static void* Refill(size_t size)
	{
		size_t nobjs = 20;
		char* chunk = ChunkAlloc(size,nobjs);
		//申请的内存块是一个的话，就直接进行返回使用
		if(nobjs == 1)
		{
			return chunk;
		}

		__TRACE_DEBUG("将剩余的生存块挂到自由链表上:%d\n", nobjs-1);

		obj* cur;
		obj* next;
		size_t index = FREELIST_INDEX(size);
		freeList[index] = cur = (obj*)(chunk+size);
		//剩下的进行挂接到自由链表中
		for(int i = 2; i<nobjs; i++)
		{
			next = (obj*)((char*)cur+size);
			cur->_freeListLink = next;
			cur = next;
		}
		//将最后一个置空
		cur->_freeListLink = NULL;
		return chunk;
	}

	//内存分配
	static void* Allocate(size_t n)
	{
		__TRACE_DEBUG("二级空间配置器申请%uBytes\n", n);

		obj* result;
		//大于128，去找一级空间配置器
		if(n > _MAX_BYTES)
		{
			 return _MallocAllocTemplate<0>::Allocate(n);
		}

		//否则就到二级空间配置器中，到自由链表中去
		size_t index = FREELIST_INDEX(n);
		result = freeList[index];
		//自由链表为空
		if(result == 0)
		{
			void* r = Refill(ROUND_UP(n));
			return r;
		}
		__TRACE_DEBUG("在自由链表第%d个位置取内存块\n", index);
		//不为空，直接取出，就是进行头删
		freeList[index] = result->_freeListLink;
		return result;
	}

	//内存的还回
	static void Deallocate(void* p,size_t n)
	{
		__TRACE_DEBUG("二级空间配置器释放%uBytes\n", n);

		//大于128，就让一级空间配置器进行处理
		if(n > _MAX_BYTES)
		{
			_MallocAllocTemplate<0>::Deallocate(p);
		}

		//否则交给二级,头插回自由链表中
		size_t index =  FREELIST_INDEX(n);
		((obj*)p)->_freeListLink = _freeList[index];
		_freeList[index] = temp;
		
	}

};


//全局变量的定义

template<bool threads,int inst>
//注意此处内嵌类型，要加typename
typename _DefaultAllocTemplate<threads,inst>
	::Obj* _DefaultAllocTemplate<threads,inst>
	::freeList[_NFREELISTS] = {0};

template<bool threads,int inst>
char* _DefaultAllocTemplate<threads,inst>::startFree= 0;

template<bool threads,int inst>
char* _DefaultAllocTemplate<threads,inst>::endFree= 0;

template<bool threads,int inst>
size_t _DefaultAllocTemplate<threads,inst>::heapSize= 0;;

#ifdef __USE_MALLOC
	typedef _MallocAllocTemplate<0> _MallocAlloc;
#else
	typedef _DefaultAllocTemplate<0, 0> Alloc;
#endif

//具体是条用哪一级空间配置器
template<class T, class _Alloc = Alloc>
class SimpleAlloc {

public:
    static T *Allocate(size_t n)
	{ return 0 == n? 0 : (T*) Alloc::Allocate(n * sizeof (T)); }

    static T *Allocate(void)
	{ return (T*) Alloc::Allocate(sizeof (T)); }

    static void Deallocate(T *p, size_t n)
	{ if (0 != n) Alloc::Deallocate(p, n * sizeof (T)); }

    static void Deallocate(T *p)
	{ Alloc::Deallocate(p, sizeof (T)); }
};



