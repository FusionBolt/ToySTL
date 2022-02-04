#pragma once
#ifndef LIST_HPP
#define LIST_HPP
#include"allocator.hpp"
#include"iterator.hpp"
#include<iostream>
namespace sp 
{
	template<typename Ty, typename Alloc = allocator<Ty>>
	class list
	{
	private:
		struct _list_node
		{
			using link_type = _list_node * ;
			link_type prev;
			link_type next;
			Ty data;
			_list_node(const Ty& x) :prev(nullptr), next(nullptr), data(x) {}
			_list_node(Ty&& x) :prev(nullptr), next(nullptr) { using std::swap; swap(data, x); }
			//
		};
	public:
		using value_type = Ty;
		using pointer = Ty * ;
		using const_pointer = const Ty*;
		using reference = Ty & ;
		using const_reference = const Ty&;
		using size_type = size_t;
		using difference_type = std::ptrdiff_t;
		class iterator;
		class const_iterator;
		//using const_iterator = const iterator;
		using reverse_iterator = sp::reverse_iterator<iterator>;
		using const_reverse_iterator = sp::reverse_iterator<const_iterator>;
		using link_type = _list_node * ;
		using list_node_allocator = typename Alloc::template rebind<_list_node>::other;


        class iterator
        {
            friend class list;
        public:
            using _Unchecked_type = std::iterator<std::bidirectional_iterator_tag, T, ptrdiff_t, T*, T&>;
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type = typename list::value_type;
            using difference_type = typename list::difference_type;
            using pointer = typename list::link_type;
            // link type
            using reference = typename list::reference;
            using const_reference = typename list::const_reference;

            iterator() = default;
            iterator(const pointer p) :p_(p) {}
            iterator(const_iterator p) : p_(p.p_) {}

            reference operator*()
            {
                return p_->data;
            }
            pointer operator->() const
            {
                return &(operator*());
            }
            const_reference operator*() const
            {
                return p_->data;
            }
            iterator operator+(difference_type n)
            {
                auto newP = p_;
                for (difference_type i = 0; i < n; ++i)
                {
                    newP = newP->next;
                }
                return iterator(newP);
            }
            iterator operator-(difference_type n)
            {
                auto newP = p_;
                for (difference_type i = 0; i < n; ++i)
                {
                    newP = newP->prev;
                }
                return iterator(newP);
            }
            iterator& operator++()
            {
                p_ = p_->next;
                return *this;
            }
            iterator& operator--()
            {
                p_ = p_->prev;
                return *this;
            }
            iterator operator++(int)
            {
                auto newP = *this;
                p_ = p_->next;
                return newP;
            }
            iterator& operator--(int)
            {
                auto newP = *this;
                p_ = p_->prev;
                return newP;
            }

            bool operator==(const iterator& other) const
            {
                return p_ != other.p_;
            }
            bool operator!=(const iterator& other) const
            {
                return p_ != other.p_;
            }
            //private:
            list::link_type p_;
        };


        class const_iterator
        {
            friend class list;
        public:
            using _Unchecked_type = std::iterator<std::bidirectional_iterator_tag, T, ptrdiff_t, T*, T&>;
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type = typename list::value_type;
            using difference_type = typename list::difference_type;
            using pointer = typename list::link_type;
            using const_pointer = typename list::const_pointer;
            // link type
            using reference = typename list::reference;
            using const_reference = typename list::const_reference;

            const_iterator() = default;
            const_iterator(std::nullptr_t) :p_(nullptr) {};
            const_iterator(const pointer p) :p_(p) {}
            const_iterator(const typename list::iterator p) :p_(p.p_) {}

            const_reference operator*()
            {
                return p_->data;
            }
            pointer operator->() const
            {
                //return &(operator*());
                return p_;
            }
            const_reference operator*() const
            {
                return p_->data;
            }
            const_iterator operator+(difference_type n)
            {
                auto newP = p_;
                for (difference_type i = 0; i < n; ++i)
                {
                    newP = newP->next;
                }
                return const_iterator(newP);
            }
            const_iterator operator-(difference_type n)
            {
                auto newP = p_;
                for (difference_type i = 0; i < n; ++i)
                {
                    newP = newP->prev;
                }
                return const_iterator(newP);
            }
            const_iterator& operator++()
            {
                p_ = p_->next;
                return *this;
            }
            const_iterator& operator--()
            {
                p_ = p_->prev;
                return *this;
            }
            const_iterator operator++(int)
            {
                auto newP = *this;
                p_ = p_->next;
                return newP;
            }
            const_iterator& operator--(int)
            {
                auto newP = *this;
                p_ = p_->prev;
                return newP;
            }

            bool operator==(const const_iterator& other) const
            {
                return p_ != other.p_;
            }
            bool operator!=(const const_iterator& other) const
            {
                return p_ != other.p_;
            }
            //private:
            list::link_type p_;
        };



		explicit list(size_type count, const Ty& x = Ty())
		{
			empty_initialize();
			auto node = node_;
			for (size_type i = 0; i < count; ++i)
			{
				auto newNode = _create_node(x);
				node->next = newNode;
				newNode->prev = node;
				node = node->next;
			}
			node->next = node_;
			node_->prev = node;
		}
		list(const list& other) :list(other.begin(), other.end()) {}
		list(list&& other)
		{
			swap(other);
		}
		list& operator=(const list& other)
		{
			swap(list(other));
			return *this;
		}
		list& operator=(list&& other)
		{
			swap(other);
			return *this;
		}
		template<typename InputIterator>
		list(InputIterator first, InputIterator last)
		{
			empty_initialize();
			auto node = node_;
			while (first != last)
			{
				auto newNode = _create_node(*first++);
				node->next = newNode;
				newNode->prev = node;
				node = node->next;
			}
			node->next = node_;
			node_->prev = node;
		}
		list(std::initializer_list<Ty> initList) :list(initList.begin(), initList.end()) {}
		list& operator=(std::initializer_list<Ty> initList)
		{
			swap(list(initList.begin(), initList.end()));
			return *this;
		}

		reference front() { return *begin(); }
		const_reference front() const { return *begin(); }
		reference back() { return *(end().prev); }
		const_reference back() const { return *(end().prev); }

		iterator begin() noexcept { return iterator(node_->next); }
		const_iterator begin() const noexcept { return const_iterator(node_->next); }
		const_iterator cbegin() const noexcept { return const_iterator(node_->next); }
		iterator end() noexcept { return iterator(node_); }
		const_iterator end() const noexcept { return const_iterator(node_); }
		const_iterator cend() const noexcept { return const_iterator(node_); }
		reverse_iterator rbegin() noexcept { return reverse_iterator(begin()); }
		const_reverse_iterator rbegin() const noexcept{ return const_reverse_iterator(cbegin()); }
		const_reverse_iterator crbegin() const noexcept{ return const_reverse_iterator(cbegin()); }
		reverse_iterator rend() noexcept { return reverse_iterator(end()); }
		const_reverse_iterator rend() const noexcept { return const_reverse_iterator(cend()); }
		const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cend()); }

		bool empty() const noexcept { return begin() == end(); }
		size_type size() const noexcept { return distance(begin(), end()); }
		size_type max_size() { return std::numeric_limits<size_type>::max(); }

		void clear() noexcept
		{
			auto node = begin();
			while (node != end())
			{
				list_node_allocator::deallocate(node++);
			}
			node_->next = node_;
			node_->prev = node_;
		}

		iterator insert(const_iterator pos, const Ty& value)
		{
			//link_type node = _create_node(value);
			//auto before = pos->prev;
			//_bind(node, pos.p_);
			//_bind(before, node);
			////before->next = node;
			////node->next = pos;
			////pos->prev = node;
			////node->prev = before;
			//return iterator(node);
			return insert(pos, 1, value);
		}
		iterator insert(const_iterator pos, Ty&& value)
		{
			link_type node = _create_node(value);
			auto before = pos->prev;
			_bind(node, pos.p_);
			_bind(before, node);
			return iterator(node);
		}
		iterator insert(const_iterator pos, size_type count, const Ty& value)
		{
			auto before = pos->prev;
			for (size_type i = 0; i < count; ++i)
			{
				link_type node = _create_node(value);
				_bind(before, node);
				before = node;
			}
			_bind(before, pos.p_);
			return iterator(before);
		}
		template<typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			auto before = pos->prev;
			while(first != last)
			{
				link_type node = _create_node(*first++);
				_bind(before, node);
				before = node;
			}
			_bind(before, pos.p_);
			return iterator(before);
		}
		iterator insert(const_iterator pos, std::initializer_list<Ty> initList)
		{
			insert(pos, initList.begin(), initList.end());
		}

		iterator erase(const_iterator pos)
		{
			auto before = pos->prev;
			auto next = pos->next;
			_bind(before, next);
			//before->next = next;
			//next->prev = before;
			_de_create(pos.p_);
			return next;
		}
		iterator erase(const_iterator first, const_iterator last)
		{
			if (first != last)
			{
				auto before = first->prev;
				while (first != last)
				{
					_de_create(first->prev);
					++first;
				}
				//before->next = last;
				//last->prev = before;
				_bind(before, last->prev);
				return last.p_;
			}
			return end();
		}

		void push_front(const Ty& value) { insert(begin(), value); }
		void push_front(Ty&& value) { insert(begin(), value); }
		void push_back(const Ty& value) { insert(end(), value); }
		void push_back(Ty&& value) { insert(end(), value); }
		void pop_back() noexcept { erase(--end()); }
		void pop_front() noexcept { erase(begin()); }

		template<class... Args>
		iterator emplace(const_iterator pos, Args&&... args)
		{
			// �������ܷ���ʾ��ָ��
			auto node = _create_node(std::forward<Args>(args)...);
			
			auto prev_node = pos.p_->prev;
			prev_node->next = node;
			node->prev = prev_node;
			node->next = pos.p_;
			pos.p_->prev = node;
			return iterator(node);
		}
		template<class... Args>
		void emplace_front(Args&&... args) { emplace(begin(), std::forward<Args>(args)...); }
		template<class... Args>
		void emplace_back(Args&&... args) { emplace(--end(), std::forward<Args>(args)...); }

		void resize(size_type count, T value = T()) { resize(count, value); }
		void resize(size_type count) { resize(count, T()); }
		void resize(size_type count, const value_type& value)
		{
			auto first = begin();
			while (first != end())
			{
				++first;
			}
			if (size() > count)
			{
				erase(first, end());
			}
			else
			{
				insert(first, size()-count, value);
			}
		}

		void merge(list&& other)
		{
			merge(std::forward(other), [](const_reference a, const_reference b) {return a > b; });
		}
		template<class Compare>
		void merge(list&&other, Compare comp) // a > b?
		{
			auto first1 = begin();
			auto last1 = end();
			auto first2 = other.begin();
			auto last2 = other.end();
			while (first1 != last1 && first2 != last2)
			{
				if (comp(*first1, *first2))
				{
					++first1;
				}
				else
				{
					transfer(first1, first2, first2+1);
					++first2;
				}
			}
			if (first2 != last2)
			{
				transfer(last1, first2, last2);
			}
		}

		void splice(const_iterator pos, list&& other)
		{
			transfer(pos, other.begin(), other.end());
		}
		void splice(const_iterator pos, list&&other, const_iterator it)
		{
			auto i = it;
			++i;
			if (pos == it || pos == i)
				return;
			transfer(pos, it, i);
		}
		void splice(const_iterator pos, list&&other, const_iterator first, const_iterator last)
		{
			if(!other.empty())
				transfer(pos, first, last);
		}
		
		void reverse() noexcept
		{
			if (node_->next == node_ || node_->next->next == node_)
				return;
			auto first = begin();
			++first;
			while (first != end())
			{
				auto old = first;
				++first;
				transfer(begin(), old, first);
			}
		}
		
		// remove�����ڲ���
		size_type remove(const_reference value)
		{
			return remove_if([&](const_reference now) {return now == value; });
		}
		template<typename UnaryPredicate>
		size_type remove_if(UnaryPredicate p)
		{
			size_type count = 0;
			auto first = begin();
			while (first != end())
			{
				auto next = first;
				++next;
				//if (*first == value)
				if (p(*first))
				{
					erase(first);
					++count;
				}
				first = next;
			}
			return count;
		}

		size_type unique()
		{
			return unique([](const_reference a, const_reference b) { return a == b; });
		}
		template<typename BinaryPredicate>
		size_type unique(BinaryPredicate p)
		{
			int count = 0;
			auto first = begin();
			auto last = end();
			while (first != last)
			{
				auto next = first;
				++next;
				if (p(*first, *next))
				{
					erase(next);
					++count;
					continue;
				}
				++first;
			}
			return count;
		}

		void sort()
		{
			sort([](const_reference a, const_reference b) { return a == b; });
		}
		template<typename Compare>
		void sort(Compare comp);

		void swap(list& other)
		{
//			using std::swap;
//            swap(node_, other.node_);
            auto n = node_;
            node_ = other.node_;
            other.node_ = n;
		}
	private:
		link_type node_;
		//link_type get_node() { return list_node_allocator::allocate(); }
		link_type _create_node(const Ty& x = Ty())
		{
			auto node = list_node_allocator::allocate();
			list_node_allocator::construct(node, _list_node(x));
			return node;
		}
		link_type _create_node(Ty&& x)
		{
			auto node = list_node_allocator::allocate();
			list_node_allocator::construct(node, _list_node(x));
			return node;
		}
		template<class... Args>
		link_type _create_node(Args&&... args)
		{
			auto node = list_node_allocator::allocate();
			list_node_allocator::construct(node, std::forward<Args>(args)...);
			return node;
		}
		void _de_create(link_type p)
		{
			list_node_allocator::destroy(p);
			list_node_allocator::deallocate(p);
		}
		void empty_initialize() 
		{
			//node_ = get_node();
			node_ = list_node_allocator::allocate();
			node_->next = node_;
			node_->prev = node_;
		}
		void _bind(link_type prev, link_type next)
		{
			prev->next = next;
			next->prev = prev;
		}
		void transfer(iterator position, iterator first, iterator last)
		{
			//auto p = position.p_->prev;
			position.p_->prev->next = first.p_;
			last.p_->prev->next = position.p_;
			first.p_->prev->next = last.p_;
			auto temp = first.p_->prev;
			first.p_->prev = position.p_->prev;
			position.p_->prev = last.p_->prev;
			last.p_->prev = temp;
		}
	};


}

#endif