#pragma once
#ifndef CONSTRUCT_HPP
#define CONSTRUCT_HPP
#include<new>
#include<utility>
#include<type_traits>
#include<iterator>
#include<cstddef>
namespace sp {
	template<typename Ty>
	void construct(Ty* ptr, const Ty& val)
	{
		::new((void*)ptr) Ty(val);
	}

	template<typename Ty>
	void construct(Ty* ptr, Ty&& val)
	{
		::new((void*)ptr) Ty(val);
	}

	template<typename Ty, typename...Args>
	void construct(Ty* ptr, Args&& ...args)
	{
		::new((void*)ptr) Ty(std::forward<Args>(args)...);
	}

	template<typename Ty>
	void _destroy(Ty* p, std::true_type) {}

	template<typename Ty>
	void _destroy(Ty* p, std::false_type)
	{
		if (p != nullptr)
		{
			p->~Ty();
		}
	}

	template<typename ForwardIter>
	void _destroy_range(ForwardIter first, ForwardIter last, std::true_type) {}

	template<typename ForwardIter>
	void _destroy_range(ForwardIter first, ForwardIter last, std::false_type)
	{
		for (; first != last; ++last)
		{
			destroy(&*first);
		}
	}

	template<typename Ty>
	void destroy(Ty* p)
	{
		_destroy(p, std::is_trivially_destructible<Ty>{});
	}

	template<typename ForwardIter>
	void destroy(ForwardIter first, ForwardIter last)
	{
		_destroy_range(first, last,
			std::is_trivially_destructible<
			typename std::iterator_traits<ForwardIter>::value_type>{}
		);
	}
}
#endif