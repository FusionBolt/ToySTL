//
// Created by fusionbolt on 2019/4/17.
//

#ifndef STL_MEMORY_HPP
#define STL_MEMORY_HPP
namespace sp {
    template<typename Alloc>
    struct allocator_traits {
        using allocator_type = Alloc;
        using value_type = Alloc::value_type;
        using pointer = Alloc::pointer;
        // don't exist is value_type*;
        using const_pointer = Alloc::const_pointer;

        // std::pointer_traits<pointer>::rebind<const value_type>;
        using void_pointer = ALloc::void_pointer;
        // std::pointer_traits<pointer>::difference_type
                using difference_type = Alloc::difference_type;
        // std::make_unsigned<difference_type>::type
        using size_type = Alloc::size_type;
        // std::make_
    };
}
#endif //STL_MEMORY_HPP
