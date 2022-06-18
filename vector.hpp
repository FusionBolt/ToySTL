#pragma once
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include"allocator.hpp"
#include"construct.hpp"
#include"iterator.hpp"
#include<algorithm>
#include<memory>
#include<utility>
#include<cstddef>
#include<iostream>
#include<limits>
namespace sp 
{
	// ��û�б��з�����ʵ����ʹ���˷������ľ�̬����
	template<typename Ty, typename Alloc = allocator<Ty>>
	class vector {
	public:
		using value_type = Ty;
		using allcator_type = Alloc;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type & ;
		using const_reference = const Ty &;
		using pointer = Ty * ;
		using const_pointer = const Ty *;
		class iterator;
		class const_iterator;
		using alloc = Alloc;
		using reverse_iterator = sp::reverse_iterator<iterator>;
		using const_reverse_iterator = sp::reverse_iterator<const_iterator>;


        class iterator
        {
            friend class vector;
        public:
            using _Unchecked_type = std::iterator<std::random_access_iterator_tag, Ty, ptrdiff_t, Ty*, Ty&>;
            using iterator_category = std::random_access_iterator_tag;
            using value_type = typename vector::value_type;
            using difference_type = typename vector::difference_type;
            using pointer = typename vector::pointer;
            using reference = typename vector::reference;
            using const_reference = typename vector::const_reference;

            iterator() = default;
            iterator(std::nullptr_t) :p_(nullptr) {};
            iterator(const pointer p) :p_(p) {}
            iterator(vector::const_iterator other) : p_(const_cast<pointer>(other.p_)) {}
            iterator& operator=(const iterator& other)
            {
                p_ = other.p_;
                return *this;
            }

            reference operator*()
            {
                return *p_;
            }
            reference operator[](difference_type n)
            {
                return *(p_ + n);
            }
            const_reference operator*() const
            {
                return *p_;
            }
            const_reference operator[](difference_type n) const
            {
                return *(p_ + n);
            }

            iterator& operator+=(difference_type n)
            {
                p_ += n;
                return *this;
            }
            iterator& operator-=(difference_type n)
            {
                p_ -= n;
                return *this;
            }
            iterator& operator++()
            {
                ++p_;
                return *this;
            }
            iterator& operator--()
            {
                --p_;
                return *this;
            }
            iterator operator++(int)
            {
                auto self = *this;
                ++p_;
                return self;
            }
            iterator operator--(int)
            {
                auto self = *this;
                --p_;
                return self;
            }

            iterator operator+(difference_type n) const
            {
                return static_cast<iterator>(p_ + n);
            }
            iterator operator-(difference_type n) const
            {
                return static_cast<iterator>(p_ - n);
            }
            difference_type operator-(const iterator& other) const
            {
                return p_ - other.p_;
            }
            bool operator<(const iterator& other) const
            {
                return p_ < other.p_;
            }
            bool operator>(const iterator& other) const
            {
                return p_ > other.p_;
            }
            bool operator<=(const iterator& other) const
            {
                return p_ <= other.p_;
            }
            bool operator>=(const iterator& other) const
            {
                return p_ >= other.p_;
            }
            bool operator==(const iterator& other) const
            {
                return p_ == other.p_;
            }
            bool operator!=(const iterator& other) const
            {
                return p_ != other.p_;
            }

        //private:
            pointer p_;
        };

        class const_iterator
        {
            friend class vector;
        public:
            using _Unchecked_type = std::iterator<std::random_access_iterator_tag, Ty, ptrdiff_t, Ty*, Ty&>;
            using iterator_category = std::random_access_iterator_tag;
            using value_type = typename vector::value_type;
            using difference_type = typename vector::difference_type;
            using pointer = typename vector::pointer;
            using const_pointer = typename vector::const_pointer;
            using reference = typename vector::reference;
            using const_reference = typename vector::const_reference;

            explicit const_iterator() = default;
            const_iterator(std::nullptr_t) :p_(nullptr) {};
            const_iterator(const_pointer pointer) :p_(pointer) {}
            // const const_pointer x
            const_iterator(const typename vector::iterator iterator) : p_(iterator.p_) {}
            const_iterator& operator=(const const_iterator& other)
            {
                p_ = other.p_;
                return *this;
            }

            const_reference operator*()
            {
                return *p_;
            }
            const_reference operator[](difference_type n)
            {
                return *(p_ + n);
            }
            const_reference operator*() const
            {
                return *p_;
            }
            const_reference operator[](difference_type n) const
            {
                return *(p_ + n);
            }

            const_iterator& operator+=(difference_type n)
            {
                p_ += n;
                return *this;
            }
            const_iterator& operator-=(difference_type n)
            {
                p_ -= n;
                return *this;
            }
            const_iterator& operator++()
            {
                ++p_;
                return *this;
            }
            const_iterator& operator--()
            {
                --p_;
                return *this;
            }
            const_iterator operator++(int)
            {
                auto self = *this;
                ++p_;
                return self;
            }
            const_iterator operator--(int)
            {
                auto self = *this;
                --p_;
                return self;
            }

            const_iterator operator+(difference_type n) const
            {
                return const_iterator(p_ + n);
            }
            const_iterator operator-(difference_type n) const
            {
                return const_iterator(p_ - n);
            }
            difference_type operator-(const const_iterator& other) const
            {
                return p_ - other.p_;
            }
            bool operator<(const const_iterator& other) const
            {
                return p_ < other.p_;
            }
            bool operator>(const const_iterator& other) const
            {
                return p_ > other.p_;
            }
            bool operator<=(const const_iterator& other) const
            {
                return p_ <= other.p_;
            }
            bool operator>=(const const_iterator& other) const
            {
                return p_ >= other.p_;
            }
            bool operator==(const const_iterator& other) const
            {
                return p_ == other.p_;
            }
            bool operator!=(const const_iterator& other) const
            {
                return p_ != other.p_;
            }

        private:
            const_pointer p_;
        };





		vector()
		{
			_alloc_and_fill();
		}
		explicit vector(size_type count,const Ty& value = Ty())
		{
			_alloc_and_fill(count, value);
		}
		template<typename InputIterator>
		vector(InputIterator first, InputIterator last):begin_(alloc::allocate(last - first))
		{
			auto newEnd = std::move(first, last, begin());
			last_ = end_ = newEnd;
		}

		vector(vector&& other)
		{
			// init member, prevent free garbage address in other.
			_alloc_and_fill();
			swap(other);
		}
		vector(const vector& other)	:vector(other.begin(),other.end()) {}

		// we have operator = (init_list) by implict cast.
		vector(std::initializer_list<Ty> list) :vector(list.begin(), list.end()) {}

		// These is always need a copy, so pass it by value.
		vector& operator=(vector other)
		{
			swap(other);
			return *this;
		}

		~vector()
		{
			_destroy_and_deallocate();
		}

		// access
		reference operator[](size_type sub) { return *(begin_ + sub); }
		const_reference operator[](size_type sub) const { return *(begin_ + sub); }
		reference at(size_type sub)
		{
			if (sub >= size() || sub < 0)
				throw std::runtime_error("sub error");
			return *(begin_ + sub);
		}
		reference front() { return *begin_; }
		const_reference front() const { return *begin_; }
		reference back() { return *(end_ - 1); }
		const_reference back() const { return *(end_ - 1); }
		pointer data() noexcept { return begin_.p_; }
		const_pointer data() const noexcept { return begin_.p_; }

		// iterator
		iterator begin() noexcept { return begin_; }
		const_iterator begin() const noexcept { return const_iterator(begin_); }
		const_iterator cbegin() const noexcept { return const_iterator(begin_); }
		iterator end() noexcept { return end_; }
		const_iterator end() const noexcept { return const_iterator(end_); }
		const_iterator cend() const noexcept { return const_iterator(end_); }
		reverse_iterator rbegin() noexcept { return reverse_iterator(begin()); }
		const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(cbegin()); }
		const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cbegin()); }
		reverse_iterator rend() noexcept { return reverse_iterator(end()); }
		const_reverse_iterator rend() const noexcept { return const_reverse_iterator(cend()); }
		const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cend()); }

		// capacity
		bool empty() noexcept { return begin_ == end_; }
		size_type size() const noexcept { return static_cast<size_type>(end_ - begin_); }
		size_type max_size() { return std::numeric_limits<size_type>::max(); }

		void reserve(size_type newCap)
		{
			if (newCap > capacity())
			{
				iterator newBegin(alloc::allocate(newCap));
				auto newEnd = std::uninitialized_copy(begin(), end(), newBegin);
				_destroy_and_deallocate();
				begin_ = newBegin;
				end_ = newEnd;
				last_ = begin_ + newCap;
			}
		}
		size_type capacity() const noexcept { return static_cast<size_type>(last_ - begin_); }

		void shrink_to_fir()
		{
			reserve(size());
		}

		// modifier
		void clear() noexcept
		{
			erase(begin(), end());
		}
		// const_iterator
		iterator _insert_later(iterator pos, size_type n, const Ty& value)
		{
			if (n > 0)
			{
				if ((size() + n) > capacity())
				{
					auto newSize = (size() > n ? size() : n) * 2;
					iterator newBegin(alloc::allocate(newSize));

					auto newEnd = std::uninitialized_copy(begin(), pos, newBegin);
					newEnd = std::uninitialized_fill_n(newEnd, n, value);
					auto newPos = newEnd;
					newEnd = std::uninitialized_copy(pos, end(), newEnd);
					// move or copy?
					_destroy_and_deallocate();
					begin_ = newBegin;
					end_ = newEnd;
					last_ = begin_ + newSize;
					return newPos;
				}
				else
				{
					size_type elems_after = end() - pos;
					auto oldEnd = end();
					//Ty value_copy = value;
					if (elems_after > n)
					{
						std::uninitialized_copy(end() - n, end(), end());
						end_ += n;
						std::copy_backward(pos, oldEnd - n, oldEnd);
						auto newPos = std::fill_n(pos, n, value);
						return newPos;
					}
					else
					{
						std::uninitialized_fill_n(end(), n - elems_after, value);
						end_ += n - elems_after;
						std::uninitialized_copy(pos, oldEnd, end());
						end_ += elems_after;
						std::fill(pos, oldEnd, value);
						return oldEnd;
					}
				}
			}
			return iterator();
		}
		iterator insert(const_iterator pos, const Ty& value)
		{
			return _insert_later(iterator(pos), 1, value);
		}
		iterator insert(const_iterator pos, Ty&& value)
		{
			return _insert_later(iterator(pos), 1, value);
		}
		iterator insert(const_iterator pos, size_type count, const Ty& value)
		{
			return _insert_later(iterator(pos), count, value);
		}
		//const_iterator
		iterator erase(const_iterator position)
		{
			iterator pos(position);
			if (pos + 1 != end())
			{
				std::copy(pos + 1, end(), pos);
			}
			--end_;
			alloc::destroy(end_.p_);
			return pos;
		}
		// const_iterator
		iterator erase(const_iterator first_i, const_iterator last_i)
		{
			iterator first(first_i), last(last_i);
			auto copyLast = std::copy(last, end(), first);
			alloc::destroy(copyLast, end());
			end_ -= last - first;
			return first;
		}

		void push_back(const Ty& value)
		{
			insert(cend(), value);
		}
		void push_back(Ty&& value)
		{
			insert(cend(), value);
		}

		template<typename...Args> // const_iterator
		iterator emplace(const_iterator position, Args&&... args)
		{
			iterator pos(position);
			if (end_ == last_)
			{
				auto newSize = size() * 2;
				iterator newBegin(alloc::allocate(newSize));
				auto newEnd = std::uninitialized_copy(begin(), pos, newBegin);
				alloc::construct(newEnd.p_, std::forward<Args>(args)...);
				auto newPos = newEnd++;
				newEnd = std::uninitialized_copy(pos, end(), newEnd);

				_destroy_and_deallocate();
				begin_ = newBegin;
				end_ = newEnd;
				last_ = begin_ + newSize;
				return newPos;
			}
			else
			{
				auto newEnd = std::uninitialized_copy(end() - 1, end(), end());
				end_ = newEnd;
				std::copy(pos, end() - 1, pos + 1);
				sp::destroy(pos.p_);
				alloc::construct(pos.p_, std::forward<Args>(args)...);
				return pos;
			}
		}


		template<typename...Args>
		iterator emplace_back(Args&&... args)
		{
			return emplace(cend(), std::forward<Args>(args)...);
		}



		void pop_back() noexcept
		{
			alloc::destroy(end_.p_);
			--end_;
		}
		void resize(size_type count)
		{
			if (count < size())
			{
				while (end_ != begin_ + count)
				{
					--end_;
					alloc::destroy(end_.p_);
				}
			}
			else if (count > size())
			{
				if (count > capacity())
				{
					reserve(count);
				}
				for (auto begin = end_; begin != end_ + count; ++begin)
				{
					alloc::construct(begin.p_, Ty());
				}
			}
		}
		void swap(vector& other) noexcept
		{
			using std::swap;
			swap(begin_.p_, other.begin_.p_);
			swap(end_.p_, other.end_.p_);
			swap(last_.p_, other.last_.p_);
		}

	private:
		iterator begin_;
		iterator end_;
		iterator last_;
		void _alloc_and_fill(size_type size = 0, value_type n = value_type())
		{
			begin_ = iterator(alloc::allocate(size));
			last_ = begin_ + size;
			end_ = begin_;
			while (end_ != begin_ + size)
			{
				alloc::construct(end_.p_, n);
				++end_;
			}
		}
		void _destroy_and_deallocate()
		{
			destroy(begin_.p_, end_.p_);
			alloc::deallocate(begin_.p_);
			begin_ = end_ = last_ = nullptr;
		}
	};

	template <typename Ty, typename Alloc>
	inline void swap(vector<Ty, Alloc> &lhs, vector<Ty, Alloc> &rhs) noexcept // We not move Ty actually.
	{
		lhs.swap(rhs);
	}


}

#endif
