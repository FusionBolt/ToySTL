#pragma once
#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP
#include<new>
#include"construct.hpp"
namespace sp 
{
	template<typename Ty>
	class allocator 
	{
	public:
		using pointer = Ty * ;
		using const_pointer = const Ty*;
		using reference = Ty & ;
		using const_reference = const Ty&;
		using value_type = Ty;
		using size_type = size_t;
		using difference_type = std::ptrdiff_t;

		template<typename U>
		struct rebind
		{
			using other = allocator<U>;
		};

		static pointer allocate()
		{
			return static_cast<Ty*>(::operator new(sizeof(Ty)));
		}

		static pointer allocate(size_t n)
		{
			return n > 0 ? static_cast<Ty*>(::operator new(n * sizeof(Ty))) : nullptr;
		}

		static void deallocate(Ty* ptr, size_t n = 1)
		{
			if (ptr == nullptr)
				return;
			::operator delete(ptr);
		}

		static void construct(Ty* ptr, const Ty& val)
		{
			sp::construct(ptr, val);
		}

		template<typename...Args>
		static void construct(Ty* ptr, Args&& ...args)
		{
			sp::construct(ptr, std::forward<Args>(args)...);
		}

		static void destroy(Ty* p)
		{
			sp::destroy(p);
		}

		template<typename ForwardIter>
		static void destroy(ForwardIter first, ForwardIter last)
		{
			sp::destroy(first, last);
		}
	};

}

#endif