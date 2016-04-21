#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;


//–¬∞ÊAutoptr
template <class T>
class AutoPtr
{
public:
	AutoPtr(T* ptr)
		:_ptr(ptr)
	{}

	AutoPtr(AutoPtr<T>& ap)
		:_ptr(ap._ptr)
	{
		ap._ptr = NULL;
	}

	AutoPtr<T>& operator=(AutoPtr<T>& ap)
	{
		if (&s != this)
		{
			delete _ptr;
			_ptr = ap._ptr;
			ap._ptr = NULL;
		}
	}

	~AutoPtr()
	{
		if (_ptr)
		{
			delete _ptr;
			_ptr = NULL;
		}
	}
private:
	T* _ptr;
};


void Test()
{
	AutoPtr<int> ap1(new int(1));
}

int main()
{
	Test();
	system("pause");
	return 0;
}

//AutoPtr¿œ∞Ê
#include<iostream>
using namespace std;

template<class T>
class AutoPtr
{
public:
	AutoPtr(T* ptr = NULL)
		:_ptr(ptr)
		, _owner(true)
	{}

	AutoPtr(const AutoPtr<T>& ap)
		:_ptr(ap._ptr)
	{
		ap._owner = false;
		_owner = true;
	}

	AutoPtr<T>& operator=(const AutoPtr<T>& ap)
	{
		if (&s != this)
		{
			delete _ptr;
			_ptr = ap._ptr;
			ap._owner = false;
			_owner = true;
		}
		return *this;
	}

	~AutoPtr()
	{
		if (_ptr)
		{		
			delete _ptr;
			_ptr = NULL;
			_owner = false;
		}
	}

	T* operator->()
	{
		return _ptr;
	}

	T& operator*()
	{
		return *_ptr;
	}
private:
	T* _ptr;
	bool _owner;
};

void Test()
{
	AutoPtr<int> ap1(new int(1));
	AutoPtr<int> ap2(ap1);
	AutoPtr<int> ap3 = ap1;
}

int main()
{
	Test();
	system("pause");
	return 0;
}

//scopedptr
#include<iostream>
using namespace std;

template<class T>
class ScopedPtr
{
public:
	ScopedPtr(T* ptr = NULL)
		:_ptr(ptr)
	{}

	~ScopedPtr()
	{
		if (_ptr)
		{
			delete _ptr;
			_ptr = NULL;
		}
	}

	T* operator->()
	{
		return _ptr;
	}

	T& operator*()
	{
		return *_ptr;
	}
protected:
	ScopedPtr<T>(const ScopedPtr<T>& sp);
	ScopedPtr<T>& operator=(const ScopedPtr<T>& sp);
private:
	T* _ptr;
};

void Test()
{
	ScopedPtr<int> sp1(new int(1));
}
int main()
{
	Test();
}

//ScopedArray
#include<iostream>
using namespace std;
#include<assert.h>


template<class T>
class ScopedArray
{
public:
	ScopedArray(T* ptr = NULL)
		:_ptr(ptr)
	{}

	~ScopedArray()
	{
		if (_ptr)
		{
			delete [] _ptr;
			_ptr = NULL;
		}
	}

	T& operator[](size_t index)
	{
		assert(index > 0);
		return _ptr[index];
	}
	
protected:
	ScopedArray<T>(const ScopedArray<T>& sp);
	ScopedArray<T>& operator=(const ScopedArray<T>& sp);

private:
	T* _ptr;
};

void Test()
{
	ScopedArray<int> sp1(new int[10]);
}

int main()
{
	Test();
}

//SharedPtr
#include<iostream>
using namespace std;

template<class T>
class SharedPtr
{
public:
	SharedPtr(T* ptr= NULL)
		:_ptr(ptr)
		, _pCount(new long(1))
	{}

	SharedPtr<T>(const SharedPtr<T>& sp)
		: _ptr(sp._ptr)
	{
		(*_pCount)++;
	}

	SharedPtr<T> operator=(const SharedPtr<T>& sp)
	{
		if (&s != this)
		{
			if (--(*pCount) == 0)
			{
				delete _ptr;
				_ptr = sp._ptr;
				(*pCount)++;
			}
		}
		return *this;
	}

	~SharedPtr()
	{
		if (_ptr)
		{
			if (--(*_pCount) == 0)
			{
				delete _ptr;
				delete _pCount;
				_ptr = NULL;
				_pCount = NULL;
			}
		}
	}

	T* operator->()
	{
		return _ptr;
	}

	T& operator*(size_t index)
	{
		assert(index > 0);
		return _ptr[index];
	}

private:
	T* _ptr;
	long *_pCount;
};


void Test()
{
	SharedPtr<int> sp1(new int(1));
	SharedPtr<int> sp2(sp1);
	SharedPtr<int> sp3 = sp1;
}

int main()
{
	Test();
	system("pause");
	return 0;
}


//SharedArray
#include<iostream>
using namespace std;
#include<assert.h>

template<class T>
class SharedArray
{
public:
	SharedArray(T* ptr = NULL)
		:_ptr(ptr)
		, _pCount(new long(1))
	{}

	SharedArray<T>(const SharedArray<T>& sp)
		: _ptr(sp._ptr)
	{
		(*_pCount)++;
	}

	SharedArray<T> operator=(const SharedArray<T>& sp)
	{
		if (&s != this)
		{
			if (--(*pCount) == 0)
			{
				delete _ptr;
				_ptr = sp._ptr;
				(*pCount)++;
			}
		}
		return *this;
	}

	~SharedArray()
	{
		if (_ptr)
		{
			if (--(*_pCount) == 0)
			{
				delete _ptr;
				delete _pCount;
				_ptr = NULL;
				_pCount = NULL;
			}
		}
	}

	T* operator[](size_t index)
	{
		assert(index);
		return _ptr[index];
	}
private:
	T* _ptr;
	long *_pCount;
};


void Test()
{
	SharedArray<int> sp1(new int[10]);
	SharedArray<int> sp2(sp1);
	SharedArray<int> sp3 = sp1;
}

int main()
{
	Test();
	system("pause");
	return 0;
}