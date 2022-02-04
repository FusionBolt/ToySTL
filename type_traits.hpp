#pragma once
#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP
#include"iterator.hpp"
struct _true_type{};
struct _false_type{};

template<typename type>
struct _type_traits {
	using has_trivial_default_constructor = _false_type;
	using has_trivial_copy_constructor = _false_type;
	using has_trivial_assignment_operator = _false_type;
	using has_trivial_destructor = _false_type;
	using is_POD_type = _false_type;
};

struct _type_traits<int> { // 基本类型实现特化版本
	using has_trivial_default_constructor = _true_type;
	using has_trivial_copy_constructor = _true_type;
	using has_trivial_assignment_operator = _true_type;
	using has_trivial_destructor = _true_type;
	using is_POD_type = _true_type;
};
#endif // !TRAITS_HPP
