#pragma once
#ifndef WEAK_PTR_H
#define WEAK_PTR_H
#include"shared_ptr.h"
#include<iostream>
#include<memory>
//这个函数暂存错误，类不完善
//template<typename T>
//template<typename Y>
//inline weak_ptr<T>::weak_ptr(const weak_ptr<Y> & wp) noexcept
//{
//	sp = wp.sp;
//}
namespace Sp {
	template<typename T>
	class weak_ptr {
	public:
		constexpr weak_ptr() noexcept;
		weak_ptr(const weak_ptr&) noexcept;

		template<typename Y>// Y and T
		weak_ptr(const weak_ptr<Y>&) noexcept;

		template<typename Y>
		weak_ptr(const std::shared_ptr<Y>&) noexcept;

		long use_count() const noexcept;
		bool expired() const noexcept;
		std::shared_ptr<T> lock() const noexcept;
		//owner_before()
	//private:
		//decltype(weak_ptr<T>::sp) get_ptr(); // 指针类型应该是什么
		std::shared_ptr<std::shared_ptr<T>> sp; // private?private:public
		// control // private a function return sp const/not const
	};

	template<typename T>
	constexpr weak_ptr<T>::weak_ptr() noexcept:sp(nullptr)
	{
	}

	template<typename T>
	inline weak_ptr<T>::weak_ptr(const weak_ptr & wp) noexcept
	{
		sp = wp.sp;
	}

	template<typename T>
	inline long weak_ptr<T>::use_count() const noexcept
	{
		return sp.use_count();
	}

	template<typename T>
	bool weak_ptr<T>::expired() const noexcept
	{
		return use_count() == 0;
	}

	template<typename T>
	std::shared_ptr<T> weak_ptr<T>::lock() const noexcept
	{
		return expired() ? std::shared_ptr<T>() : std::shared_ptr<T>(*this);
	}

	//template<typename T>
	//inline decltype(weak_ptr<T>::sp) weak_ptr<T>::get_ptr()
	//{
	//	return sp;
	//}

	template<typename T>
	template<typename Y>
	inline weak_ptr<T>::weak_ptr(const weak_ptr<Y> & wp) noexcept
	{
		sp = wp.sp;
	}

	template<typename T>
	template<typename Y>
	inline weak_ptr<T>::weak_ptr(const std::shared_ptr<Y>&p) noexcept
	{
		sp = p;
	} // not test

	template<typename T>
	decltype(sp) get_ptr() noexcept
	{
		return sp;
	}
}

#endif