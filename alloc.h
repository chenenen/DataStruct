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
	//������ú�������Ϣ
	fprintf(stdout,"�� %s:%d�� %s",GetFileName(filename).c_str(),line,function);

	//����û����trace��Ϣ
	va_list args;
	va_start(args,format);
	vfprintf(stdout,format,args);
	va_end(args);
#endif
} 
#define __TRACE_DEBUG(...) \
	__trace_debug(__FUNCTION__,__FILE__,__LINE__,__VA_ARGS__);






/***************************һ���ռ�������*********************/
template<int inst>
class _MallocAllocTemplate
{
public:
	
	typedef void(*HANDLER)();
	static HANDLER _mallocAllocOOmHandler;
public:
	//����ռ�
	static void* Allocate(size_t n)
	{
		__TRACE_DEBUG("һ���ռ�����������%uBytes\n", n);
		void* result = malloc(n);
		if(result == 0)
			result = OOm_Malloc(n);
		return result;
	}

	static void * OOm_Malloc(size_t n)
	{
		void* result;

		//�˴�����Ϊ��ѭ��:���ϵĵ����ڴ治�㴦����ƣ���������ĳһ���ܹ��ɹ�
		while(1)
		{
			//������c++�е�new_handler���ƣ���һ�ֿͶ�ָ���Ĵ������̡�
			//�������ڴ��ͷź���������ַ��_mallocAllocOOmHandler

			//ʧ���ˣ��׳��쳣
				if(NULL == _mallocAllocOOmHandler)
				{
					throw std::bad_alloc;
				}
			//�ٴν�������
				else
				{
					result = malloc(n);
				}
				if(result)
					return result;
		}
	}

	//�ռ���ͷ�
	static void Deallocate(void* p)
	{
		__TRACE_DEBUG("һ���ռ��������ͷ�0x%p,%uBytes\n", p,n);
		free(p);
	}

	//����ָ��ָ������һ������������������д����쳣
	//SetMallocHandler��HANDLER ָ��һ������������������д����쳣��
	//���HANDLER Ϊ�գ���ô���������û��ִ�У��ͻ����쳣��
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


/********************�����ռ�������***********************/
template<bool threads,int inst>
class _DefaultAllocTemplate
{
protected:
	enum {_ALIGN = 8};  //���������еĻ�׼ֵ
	enum {_MAX_BYTES = 128};   //��������������ֵ
	enum {_NFREELISTS = _MAX_BYTES/_ALIGN};  //���Զ�Ӧ���ٸ��±ָ꣨�����飩

	//���������нڵ�Ķ���
	union obj
	{
		obj* _freeListLink; //ָ����һ���ڴ������ָ��
		char clientData[1]; 
	};

	//����������ʵ����һ��ָ�����飨+����ҽ��ڴ�飩
	static obj* freeList[_NFREELISTS];

	//����ڴ�����ʱ���״̬
	static char* startFree;   //�ڴ�صĿ�ʼ
	static char* endFree;     //�ڴ�صĽ���
	static size_t heapSize;   //�õ������ڴ��С

/////////��ʼ�����ڴ�ķ��䴦�����///////////
public:
	//�Ƚ����±�ļ��㣬��Ҫ������������Ǹ�λ�ý����ڴ��������߹ҽ�
	//˵��:�����ڼ����±��ʱ�򣬺�����
	//�����ʱ���Ǽ��㵽��һ����Χ�У�Ȼ������±�-1�������Ͳ��ö�û��
	//�ڴ����Ľ��з��ദ����
	static  size_t FREELIST_INDEX(size_t bytes)
	{
        return (((bytes) + _ALIGN-1)/_ALIGN - 1);
	}

	//�������ʵ���Ͼ��������ڴ����
	//��һ�����ֳ������֣�ǰһ����������룬����һ����ȥ����
	//�ٸ����ӣ�7  8
	//
	//   16  8  4  2  1
	// 7: 0  0  1  1  1
	// 8: 0  1  1  1  1
	// (7+8-1)& ~(7)
	// 14:0  1  1  1  0
	// ~7:1  1  0  0  0
//�����  0  1  0  0  0
	//���Կ����Ի�׼ֵΪ��׼�ߣ��������뵽��׼ֵ��
	static size_t ROUND_UP(size_t bytes)
	{
		return (((bytes) + _ALIGN-1) & ~(_ALIGN-1));
	}

public:

	//����ڴ������
	//�����Ҫע����Ƿ���ֵ��char* ����Ȼ��֪��ν����з�
	static char* ChunkAlloc(size_t size, /*int*/size_t & nobjs)
	{
		size_t bytesToGet = 0;
		char* result;
		size_t totalBytes = size*nobjs;//��Ҫ���ڴ�����
		size_t leftBytes = endFree-startFree; //�ڴ��ʣ����ڴ�

		__TRACE_DEBUG("�ڴ��ʣ��%ubytes,��Ҫ����%uBytes\n",
					leftBytes,totalBytes);
		//���������

		//1�����ڴ���е��ڴ��㹻��������ڴ�ʱ
		if(leftBytes > totalBytes)
		{
			__TRACE_DEBUG("�ڴ����㹻%u�������С�ڴ�\n", nobjs);
			result = startFree;
			startFree += totalBytes;
			return result;
		}
		//2�����ڴ���е��ڴ����1�����ǲ����������ʱ��
		else if(leftBytes > 0)
		{
			//�ж��پ��������
			nobjs = totalBytes/size;
			totalBytes = nobjs*size;

			__TRACE_DEBUG("�ڴ�ֻ�ܹ�����%u�������С�ڴ�\n", nobjs);
			startFree += totalBytes;
			return result;
		}
		//3���ڴ������һ��size�Ĵ�С����������ʱ��Ҫȥϵͳ�н�������
		else
		{
			//ȥϵͳ��������ô����ڴ�
			bytesToGet = 2 * totalBytes + ROUND_UP(heapSize >> 4);
			//�����ڴ���п��ܻ����ڴ�,�Ƚ�����ڴ�ŵ���Ӧ���ڴ����
			if(leftBytes >0)
			{
				__TRACE_DEBUG("��ʣ���%uBytesСƬ�ڴ�ҵ�����������\n", leftBytes);

				size_t index = FREELIST_INDEX(leftBytes);
				((obj*)startFree)->_freeListLink = freeList[index];
				freeList[index] = (obj*)startFree;
			}
			startFree = (char*)malloc(bytesToGet);
			//�����ϵͳ������ʧ����,��ô�͵����������������ȥ����
			if(startFree == 0)
			{
				//__TRACE_DEBUG("����������������������ڴ�\n");

				for(int i = size; i<_MAX_BYTES; i+= _ALIGN)
				{
					size_t index = FREELIST_INDEX(leftBytes);
					//�������ɹ���
					if(freeList[index])
					{
						__TRACE_DEBUG("����������������������ڴ�\n");

						startFree = (char*)freeList[index];
						freeList[index] = ((obj*)startFree)->_freeListLink;
						endFree = startFree+i;
						return ChunkAlloc(size,nobjs);
					}
				}
			
			}
			endFree = NULL;//��ֹ�쳣

			//�����ϵͳ�ڴ涼�Խ��ˣ�Ҳ����ɽ��ˮ���ˣ��ͳ�����ȥ
			//����һ���ռ�������
			startFree = (char*)_MallocAllocTemplate<0>::Allocate(bytesToGet);
		}

		//��ϵͳ�л�õ����ֽ��������������´ε���
		heapSize += bytesToGet;
		endFree = startFree + bytesToGet;
		return ChunkAlloc(size,nobjs);
		
	}
	
	//��������ڴ��зֹҽӵ�����������
	static void* Refill(size_t size)
	{
		size_t nobjs = 20;
		char* chunk = ChunkAlloc(size,nobjs);
		//������ڴ����һ���Ļ�����ֱ�ӽ��з���ʹ��
		if(nobjs == 1)
		{
			return chunk;
		}

		__TRACE_DEBUG("��ʣ��������ҵ�����������:%d\n", nobjs-1);

		obj* cur;
		obj* next;
		size_t index = FREELIST_INDEX(size);
		freeList[index] = cur = (obj*)(chunk+size);
		//ʣ�µĽ��йҽӵ�����������
		for(int i = 2; i<nobjs; i++)
		{
			next = (obj*)((char*)cur+size);
			cur->_freeListLink = next;
			cur = next;
		}
		//�����һ���ÿ�
		cur->_freeListLink = NULL;
		return chunk;
	}

	//�ڴ����
	static void* Allocate(size_t n)
	{
		__TRACE_DEBUG("�����ռ�����������%uBytes\n", n);

		obj* result;
		//����128��ȥ��һ���ռ�������
		if(n > _MAX_BYTES)
		{
			 return _MallocAllocTemplate<0>::Allocate(n);
		}

		//����͵������ռ��������У�������������ȥ
		size_t index = FREELIST_INDEX(n);
		result = freeList[index];
		//��������Ϊ��
		if(result == 0)
		{
			void* r = Refill(ROUND_UP(n));
			return r;
		}
		__TRACE_DEBUG("�����������%d��λ��ȡ�ڴ��\n", index);
		//��Ϊ�գ�ֱ��ȡ�������ǽ���ͷɾ
		freeList[index] = result->_freeListLink;
		return result;
	}

	//�ڴ�Ļ���
	static void Deallocate(void* p,size_t n)
	{
		__TRACE_DEBUG("�����ռ��������ͷ�%uBytes\n", n);

		//����128������һ���ռ����������д���
		if(n > _MAX_BYTES)
		{
			_MallocAllocTemplate<0>::Deallocate(p);
		}

		//���򽻸�����,ͷ�������������
		size_t index =  FREELIST_INDEX(n);
		((obj*)p)->_freeListLink = _freeList[index];
		_freeList[index] = temp;
		
	}

};


//ȫ�ֱ����Ķ���

template<bool threads,int inst>
//ע��˴���Ƕ���ͣ�Ҫ��typename
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

//������������һ���ռ�������
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



