#pragma once
#ifndef SHARED_PTR_H
#define SHARED_PTR_H
#include<iostream>
#include<memory>
#include"sp_control.h"
namespace Sp {  // namespace Sp
	template<typename T>
	class shared_ptr
	{
		template <typename T, typename U>
		friend bool operator==(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept;
		template<typename T, typename U>
		friend bool operator!=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept;
		template<typename T, typename U>
		friend bool operator<(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept;
		template<typename T, typename U>
		friend bool operator>(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept;
		template<typename T, typename U>
		friend bool operator<=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept;
		template<typename T, typename U>
		friend bool operator>=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept;
		template<typename T>
		friend bool operator==(const shared_ptr<T>& lhs, std::nullptr_t rhs) noexcept;
		template<typename T>
		friend bool operator==(std::nullptr_t lhs, const shared_ptr<T>& rhs) noexcept;
		template<typename T>
		friend bool operator!=(const shared_ptr<T>& lhs, std::nullptr_t rhs) noexcept;
		template<typename T>
		friend bool operator!=(std::nullptr_t lhs, const shared_ptr<T>& rhs) noexcept;
		template<typename T>
		friend bool operator<(const shared_ptr<T>& lhs, std::nullptr_t rhs) noexcept; //
		template<typename T>
		friend bool operator<(std::nullptr_t lhs, const shared_ptr<T>& rhs) noexcept;
		template<typename T>
		friend bool operator>(const shared_ptr<T>& lhs, std::nullptr_t rhs) noexcept;
		template<typename T>
		friend bool operator>(std::nullptr_t lhs, const shared_ptr<T>& rhs) noexcept;
		template<typename T>
		friend bool operator<=(const shared_ptr<T>& lhs, std::nullptr_t rhs) noexcept;
		template<typename T>
		friend bool operator<=(std::nullptr_t lhs, const shared_ptr<T>& rhs) noexcept;
		template<typename T>
		friend bool operator>=(const shared_ptr<T>& lhs, std::nullptr_t rhs) noexcept;
		template<typename T>
		friend bool operator>=(std::nullptr_t lhs, const shared_ptr<T>& rhs) noexcept;
	public:
		using element_type = T;
		constexpr shared_ptr() noexcept;
		constexpr shared_ptr(std::nullptr_t) noexcept;
		template<typename Y>
		explicit shared_ptr(Y *p) ;

		template<typename Y, typename Deleter>
		shared_ptr(Y* ptr, Deleter d);
		template<class Deleter>
		shared_ptr(std::nullptr_t, Deleter d);// 关于空指针析构

		// alloc相关
		template<typename Y, typename Deleter, typename Alloc> // must is allocator
		shared_ptr(Y* p, Deleter d, Alloc alloc);
		template<typename Deleter, typename Alloc>
		shared_ptr(std::nullptr_t p, Deleter d, Alloc alloc);
		template<typename Y>
		shared_ptr(const shared_ptr<Y>& r, T* p) noexcept;

		shared_ptr(const shared_ptr &) noexcept; // 查找到两个匹配项 解决方案？
		template<typename Y>
		shared_ptr(const shared_ptr<Y>& r) noexcept;

		shared_ptr(shared_ptr&& r) noexcept; // 查找到两个匹配项 解决方案？
		//template<typename Y>
		//shared_ptr(shared_ptr<Y>&& r) noexcept;

		template<typename Y>
		explicit shared_ptr(const std::weak_ptr<Y>& r);
		template<typename Y, typename Deleter>
		shared_ptr(std::unique_ptr<Y, Deleter>&& r);

		~shared_ptr();

		shared_ptr<T>& operator= (const shared_ptr<T> &);
		
		T& operator*();
		T& operator*() const;
		T* operator->();
		T* operator->() const;
		T& operator[] (std::ptrdiff_t idx);

		void reset() noexcept;
		template<typename Y>
		void reset(Y* p); // cppreference
		template<typename Y, typename Deleter>
		void reset(Y* p, Deleter d);
		template<typename Y, typename Deleter, typename Alloc>
		void reset(Y* ptr, Deleter d, Alloc alloc);
		void swap(shared_ptr& r) noexcept;

		T* get() const noexcept;
		size_t use_count() const;
		explicit operator bool() const noexcept;
	private:
		T *ptr;
		sp_control<T> *control;
		
	};

	template<typename T>
	constexpr shared_ptr<T>::shared_ptr() noexcept:ptr(nullptr)
	{
		control = new sp_control<T>(nullptr);
	}

	template<typename T>
	constexpr shared_ptr<T>::shared_ptr(std::nullptr_t) noexcept : ptr(nullptr)
	{
		control = new sp_control<T>(nullptr);
	}

	template<typename T>
	shared_ptr<T>::shared_ptr(const shared_ptr &s) noexcept :ptr(s.ptr), control(s.control)
	{
		++*s.control->use_count;
	}

	template<typename T>
	template<typename Y>
	shared_ptr<T>::shared_ptr(Y *p) : ptr(p)
	{
		control = new sp_control<T>(p);
	}

	template<typename T>
	template<typename Y, typename Deleter>
	inline shared_ptr<T>::shared_ptr(Y * ptr, Deleter d)
	{
		control = new sp_control<T>(ptr, d);
	}

	template<typename T>
	template<class Deleter>
	inline shared_ptr<T>::shared_ptr(std::nullptr_t, Deleter d)
	{
		control = new sp_control<T>(nullptr, d);
	}

	template<typename T>
	template<typename Y, typename Deleter, typename Alloc>
	inline shared_ptr<T>::shared_ptr(Y * p, Deleter d, Alloc alloc):ptr(p)
	{
		control = new sp_control<T>(p, d, alloc);
	}

	template<typename T>
	template<typename Deleter, typename Alloc>
	inline shared_ptr<T>::shared_ptr(std::nullptr_t p, Deleter d, Alloc alloc):ptr(nullptr)
	{
		control = new sp_control<T>(nullptr, d, alloc);
	}

	template<typename T>
	template<typename Y>
	inline shared_ptr<T>::shared_ptr(const shared_ptr<Y>& r, T * p) noexcept:ptr(p)
	{
		control = new sp_control<T>(r.get());
	}

	template<typename T>
	inline void shared_ptr<T>::reset() noexcept
	{
		shared_ptr().swap(*this);
	}

	template<typename T>
	inline void shared_ptr<T>::swap(shared_ptr & r) noexcept
	{
		std::swap(ptr, r.ptr);
		std::swap(control, r.control);
	}

	template<typename T>
	T* shared_ptr<T>::get() const noexcept
	{
		return ptr;
	}

	template<typename T>
	shared_ptr<T>::shared_ptr(shared_ptr&& r) noexcept:ptr(r.ptr),control(r.control)
	{
		r.ptr = nullptr;
		r.control = nullptr;
	}

	template<typename T>
	template<typename Y>
	shared_ptr<T>::shared_ptr(shared_ptr<Y>&& r) noexcept:ptr(r.ptr), control(r.control)
	{
		r.ptr = nullptr;
		r.control = nullptr;
	}

	template<typename T>
	template<typename Y>
	shared_ptr<T>::shared_ptr(const std::weak_ptr<Y>& r)
	{
		auto ret = r.lock();
		if (!ret)
			throw std::runtime_error("nullptr");
		ptr = ret.get();
		control = ret.control; //
		
	}
	
	template<typename T>
	template<typename Y, typename Deleter>
	shared_ptr<T>::shared_ptr(std::unique_ptr<Y, Deleter>&& r):shared_ptr(r.release(), r.get_deleter())
	{
		// ?? 判断Deleter是否为引用 如果是引用应该调用
		// shared_ptr(r.release(), std::ref(r.get_deleter()));
	}

	template<typename T>
	template<typename Y>
	inline void shared_ptr<T>::reset(Y * p)
	{
		shared_ptr<T>(p).swap(*this);
	}

	template<typename T>
	template<typename Y, typename Deleter>
	inline void shared_ptr<T>::reset(Y * p, Deleter d)
	{
		shared_ptr<T>(p, d).swap(*this);
	}

	template<typename T>
	template<typename Y, typename Deleter, typename Alloc>
	inline void shared_ptr<T>::reset(Y * ptr, Deleter d, Alloc alloc)
	{
		shared_ptr<T>(ptr, d, alloc).swap(*this);
	}

	template<typename T>
	shared_ptr<T> & shared_ptr<T>::operator=(const shared_ptr<T> &s)
	{
		++*s.control->use_count;
		control->release();
		ptr = s.ptr;
		control = s.control;
		return *this;
	}

	template<typename T>
	inline T & shared_ptr<T>::operator*()
	{
		return *ptr;
	}

	template<typename T>
	T & shared_ptr<T>::operator*() const
	{
		return *ptr;
	}

	template<typename T>
	inline T * shared_ptr<T>::operator->()
	{
		return ptr;
	}

	template<typename T>
	inline T * shared_ptr<T>::operator->() const
	{
		return ptr;
	}

	template<typename T>
	inline T & shared_ptr<T>::operator[](std::ptrdiff_t idx)
	{
		return get()[idx];
	}

	template<typename T>
	size_t shared_ptr<T>::use_count() const
	{
		return *control->use_count;
	}

	template<typename T>
	shared_ptr<T>::operator bool() const noexcept
	{
		return get() != nullptr;
	}

	template<typename T>
	shared_ptr<T>::~shared_ptr()
	{
		control->release();
	}

	template<typename T, class... Args> // 重载
	Sp::shared_ptr<T> make_shared(Args&&... args)
	{
		return shared_ptr<T>(new T(std::forward<Args>(args)...));
	}

	template<typename T, typename U>
	bool operator==(const shared_0ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept
	{
		return lhs.get() == rhs.get();
	}

	template<typename T, typename U>
	bool operator!=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept
	{
		return !(lhs == rhs);
	}

	template<typename T, typename U>
	bool operator<(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept
	{
		// V为lhs和rhs的合成指针类型
		return std::less<V>()(lhs.get(), rhs.get());
	}

	template<typename T, typename U>
	bool operator>(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept
	{
		return rhs < lhs；
	}

	template<typename T, typename U>
	bool operator<=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept
	{
		return !(rhs < lhs);
	}

	template<typename T, typename U>
	bool operator>=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept
	{
		return !(lhs < rhs)
	}

	template<typename T>
	bool operator==(const shared_ptr<T>& lhs, std::nullptr_t rhs) noexcept
	{
		return !lhs;
	}

	template<typename T>
	bool operator==(std::nullptr_t lhs, const shared_ptr<T>& rhs) noexcept
	{
		return !rhs;
	}

	template<typename T>
	bool operator!=(const shared_ptr<T>& lhs, std::nullptr_t rhs) noexcept
	{
		return (bool)lhs;
	}

	template<typename T>
	bool operator!=(std::nullptr_t lhs, const shared_ptr<T>& rhs) noexcept
	{
		return (bool)rhs;
	}

	template<typename T>
	bool operator<(const shared_ptr<T>& lhs, std::nullptr_t rhs) noexcept
	{
		return std::less<shared_ptr<T>::element_type>()(lhs.get(), nullptr);
	}

	template<typename T>
	bool operator<(std::nullptr_t lhs, const shared_ptr<T>& rhs) noexcept
	{
		return std::less<shared_ptr<T>::element_type>()(nullptr, rhs.get());
	}

	template<typename T>
	bool operator>(const shared_ptr<T>& lhs, std::nullptr_t rhs) noexcept
	{
		return nullptr < lhs;
	}

	template<typename T>
	bool operator>(std::nullptr_t lhs, const shared_ptr<T>& rhs) noexcept
	{
		return rhs < nullptr;
	}

	template<typename T>
	bool operator<=(const shared_ptr<T>& lhs, std::nullptr_t rhs) noexcept
	{
		return !(nullptr < lhs);
	}

	template<typename T>
	bool operator<=(std::nullptr_t lhs, const shared_ptr<T>& rhs) noexcept
	{
		return !(rhs < nullptr);
	}

	template<typename T>
	bool operator>=(const shared_ptr<T>& lhs, std::nullptr_t rhs) noexcept
	{
		return !(lhs < nullptr);
	}

	template<typename T>
	bool operator>=(std::nullptr_t lhs, const shared_ptr<T>& rhs) noexcept
	{
		return !(nullptr < rhs);
	}

} // namespace Sp

#endif