#pragma once
#ifndef SP_CONTROL_H
#define SP_CONTROL_H
#include<functional>
#include<memory>
// 存在的坑 分配器
// 关于弱指针的引用计数
namespace Sp {
	template<typename T>
	class sp_control
	{
	public:
		// 赋值构造函数
		using Deleter = std::function<void(T*)>;
		using Alloc = std::allocator<T>;
		constexpr sp_control() noexcept;
		constexpr sp_control(std::nullptr_t) noexcept;
		sp_control(T*, Deleter = nullptr)noexcept; // 会产生二义调用
		sp_control(T*, Deleter = nullptr, Alloc = nullptr)noexcept;
		void swap(sp_control& r) noexcept;
		void release();
		T *ptr;
		Deleter del; // 不抛异常 如何判断是否是良式
		Alloc alloc; // ??
		size_t *use_count;
		size_t *weak_count; // nullptr
		~sp_control();
	};

	template<typename T>
	constexpr sp_control<T>::sp_control() noexcept:ptr(nullptr), del(nullptr)
	{
		use_count = new int(0);
		weak_count = new int(0);
	}

	template<typename T>
	constexpr sp_control<T>::sp_control(std::nullptr_t) noexcept: ptr(nullptr), del(nullptr)
	{
		use_count = new int(0);
		weak_count = new int(0);
	}

	template<typename T>
	inline sp_control<T>::sp_control(T *p, Deleter d) noexcept : ptr(p), del(d) {
		use_count = new size_t(1);
		weak_count = new size_t(0);
	}
	template<typename T>
	inline sp_control<T>::sp_control(T *p, Deleter d, Alloc a) noexcept:ptr(p), del(d), alloc(a)
	{
		use_count = new int(1);
		weak_count = new size_t(0);
	}
	template<typename T>
	inline void sp_control<T>::swap(sp_control & r) noexcept
	{
		std::swap(ptr);
		std::swap(del);
		std::swap(use_count);
		std::swap(weak_count);
	}
	template<typename T>
	inline void sp_control<T>::release()
	{
		if (ptr && --*use_count == 0)
		{
			del ? del(ptr) : delete ptr;
			delete use_count;
			ptr = nullptr;
			use_count = nullptr;
		}
	}
	template<typename T>
	inline sp_control<T>::~sp_control()
	{
		if (*weak_count == 0 || !use_count)
		{
			delete use_count;
			delete weak_count;
		}
	}
}
#endif