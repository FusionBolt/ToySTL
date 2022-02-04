#pragma once
#ifndef UTILITY_H
#define UTILITY_H
namespace Sp {
	template<typename T1, typename T2>
	struct pair {
		T1 first;
		T2 second;
		constexpr pair() :first(T1()), second(T2()) {}
		constexpr pair(const T1& x, const T2& y) : first(x), second(y) {}
		template<typename U1, typename U2>
		constexpr pair(U1&& x, U2&& y) : first(x), second(y) {}
		template<typename U1, typename U2>
		constexpr pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}
		template<typename U1, typename U2>
		constexpr pair(pair<U1, U2>&& p) : first(p.first), second(p.second) {}
		template<typename... Args1, class... Args2>
		// tuple
		pair(const pair& p) = default;
		pair(pair&& p) = default;
	};
}
#endif