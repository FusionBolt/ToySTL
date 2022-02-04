//
// Created by fusionbolt on 2019/4/17.
//

#ifndef STL_DEQUE_HPP
#define STL_DEQUE_HPP

#include "allocator.hpp"
#include "iterator.hpp"

#include <new>

namespace sp
{
    // 一个map管理多个确定长度的缓冲区
    // 迭代器指向这段缓冲区的起点、终点、当前位置以及所归属的map
    template<typename Ty, typename Allocator = allocator<Ty>>
    class deque
    {
    public:
        using value_type = Ty;
        using allocator_type = Allocator;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = value_type &;
        using const_reference = const reference;
        using pointer = Ty *;
        using const_pointer = const pointer;
        using map_pointer = Ty **;

        class iterator
        {
            using iterator_category = sp::random_access_iterator_tag;
            using value_type = Ty;
            using size_type = std::size_t;
            using difference_type = std::ptrdiff_t;
            using reference = value_type &;
            pointer _first, _last, _cur;
            map_pointer _p;

        };

        class map_allocator
        {
            using value_type = typename deque::pointer;
            using pointer = map_pointer;
            pointer allocate()
            {
                return static_cast<Ty*>(::operator new(sizeof(value_type)));
            }
            pointer allocate(size_t)
            {

            }
        };

        deque():_map_size(3)
        {
            ;
        }

        explicit deque(const Allocator &alloc);

        explicit deque(size_type count, const Ty &value,
                       const Allocator &alloc = Allocator());

        explicit deque(size_type count);

        template<typename InputIt>
        deque(InputIt first, InputIt last, const Allocator &alloc = Allocator());

        deque(const deque& other, const Allocator& alloc = Allocator());
        deque(deque&& other, const Allocator& alloc = Allocator());
        deque(std::initializer_list<Ty> init, const Allocator& alloc = Allocator());
    private:
        map_pointer _map;
        iterator _begin, _end;
        size_type _map_size;

    };
}
#endif //STL_DEQUE_HPP
