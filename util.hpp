#pragma once
#ifndef UTIL_HPP
#define UTIL_HPP
namespace sp {
	template<typename T>
	struct remove_reference {
		using type = T;
	};

	template<typename T>
	struct remove_reference<T&> {
		using type = T;
	};

	template<typename T>
	struct remove_reference<T&&> {
		using type = T;
	};

	template<typename T>
	inline typename sp::remove_reference<T>::type&& move(T&& _t)
	{
		return static_cast<typename sp::remove_reference<T>::type&&>(_t);
	}

	//template<typename T>
	//T&& forward(typename sp::remove_reference<T>::type t) noexcept; C++11-14
	template<typename T>
	constexpr T&& forward(typename sp::remove_reference<T>::type& t) noexcept;

	template<typename T>
	constexpr T&& forward(typename sp::remove_reference<T>::type&& t) noexcept;
}
#endif