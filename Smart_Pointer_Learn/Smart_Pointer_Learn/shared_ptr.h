#pragma once
#include <iostream>
using namespace std;

namespace self
{
	template<class T>
	class shared_ptr
	{
	public:
		explicit shared_ptr(T* ptr) :_ptr(ptr), _pcount(new int(1))
		{

		}

		shared_ptr(const shared_ptr<T>& sp)
			:_ptr(sp._ptr), _pcount(sp._pcount),_del(sp._del)
		{
			++(*_pcount);
		}
		//删除器
		template<class D>
		shared_ptr(T* ptr, D del)
			:_ptr(ptr), _del(del), _pcount(new int(1))
		{ }

		void release()
		{
			if (--(*_pcount) == 0)
			{
				_del( _ptr);
				delete _pcount;
				_ptr = nullptr;
				_pcount = nullptr;
			}
		}
		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (_ptr != sp._ptr)
			{
				release();
				_ptr = sp._ptr;
				_pcount = sp._pcount; 
				_del = sp._del;
				++(*_pcount);
			}
			return *this;
		}
		~shared_ptr()
		{
			release();
		}

		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}

		int use_count() const
		{
			return *_pcount;
		}

		T* get() const
		{
			return _ptr;
		}
	private :
		T* _ptr;
		int* _pcount;
		function<void(T*)> _del = [](T* ptr) {delete ptr; };
	};
}