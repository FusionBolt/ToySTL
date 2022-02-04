#pragma once
#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <cstddef>

namespace sp
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag :public input_iterator_tag {};
	struct bidirectional_iterator_tag :public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template<class Category,
		class T,
		class Distance = ptrdiff_t,
		class Pointer = T*,
		class Reference = T&>
	struct iterator {
		using iterator_category = Category;
		using value_type = T;
		using difference_type = Distance;
		using pointer = Pointer;
		using reference = Reference;
	};

	template<typename Iterator>
	struct iterator_traits {
		using iterator_category = typename Iterator::iterator_category;
		using value_type = typename Iterator::value_type;
		using difference_type = typename Iterator::difference_type;
		using pointer = typename Iterator::pointer;
		using reference = typename Iterator::reference;
	};

	template<typename T>
	struct iterator_traits<T*> {
		using iterator_category = random_access_iterator_tag;
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = T*;
		using reference = T&;
	};

	template<typename T>
	struct iterator_traits<const T*> {
		using iterator_category = random_access_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;
	};


	template<typename Iterator>
	typename iterator_traits<Iterator>::iterator_category
		iterator_category(const Iterator&)
	{
		using category = typename iterator_traits<Iterator>::iterator_category;
		return category();
	}

	template<typename Iterator>
	typename iterator_traits<Iterator>::difference_type*
		distance_type(const Iterator&)
	{
		return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
	}

	template<typename Iterator>
	typename iterator_traits<Iterator>::value_type*
		value_type(const Iterator&)
	{
		return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
	}
	// *???

	template<typename Iterator>
	class reverse_iterator
	{
	public:
		using iterator_category = typename sp::iterator_traits<Iterator>::iterator_category;
		using value_type = typename sp::iterator_traits<Iterator>::value_type;
		using difference_type = typename sp::iterator_traits<Iterator>::difference_type;
		using pointer = typename sp::iterator_traits<Iterator>::pointer;
		using reference = typename sp::iterator_traits<Iterator>::reference;
		using iterator_type = Iterator;
		constexpr explicit reverse_iterator(Iterator iterator) :iterator_(iterator) {}

		//template<typename U>
		//constexpr reverse_iterator(const reverse_iterator<U>& other) :iterator_(other.iterator_) {}
		reverse_iterator& operator++()
		{ 
			--iterator_;
			return *this;
		}
		reverse_iterator& operator--()
		{ 
			++iterator_;
			return *this;
		}
		reverse_iterator operator++(int) 
		{ 
			auto self = *this;
			--iterator_;
			return self;
		}
		reverse_iterator operator--(int)
		{ 
			auto self = *this;
			++iterator_;
			return self;
		}
		value_type operator*() 
		{
			return *iterator_;
		}
		bool operator==(const reverse_iterator& other) const
		{
			return iterator_ == other.iterator_;
		}
		bool operator!=(const reverse_iterator& other) const
		{
			return iterator_ != other.iterator_;
		}

		iterator_type iterator_;
	};

	template<typename InputIterator>
	typename iterator_traits<InputIterator>::difference_type
		distance(InputIterator first, InputIterator last)
	{
		using category = typename iterator_traits<InputIterator>::iterator_category;
		return _distance(first, last, category());
	}
	template<typename InputIterator>
	typename iterator_traits<InputIterator>::difference_type
		_distance(InputIterator first, InputIterator last, random_access_iterator_tag)
	{
		return last - first;
	}
	template<typename InputIterator>
	typename iterator_traits<InputIterator>::difference_type
		_distance(InputIterator first, InputIterator last, input_iterator_tag)
	{
		typename iterator_traits<InputIterator>::difference_type n = 0;
		while (first != last)
		{
			++first;  ++n;
		}
		return n;
	}
}
#endif // !ITERATOR_HPP