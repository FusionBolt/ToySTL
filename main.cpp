#include<iostream>
#include<memory>
#include"vector.hpp"
#include<vector>
//using namespace Sp;
class A {
public:
	static int p;
	A() { std::cout << "A" << ++p << " "; }
	~A() { std::cout << "~A" << --p << " "; }
};
int A::p = 0;
class B {
public:
	B();
	B(const B&) = delete;
	B& operator=(const B&) = delete;
};
void vec()
{
	{
		std::vector<A> v{ A(), A(), A()};
		std::cout << std::endl;
		v.reserve(1);
		std::cout << std::endl;
	}
	std::cin.get();
}

void problem2()
{
	{
		A a, b, c, d, e, f, g;
		std::cout << std::endl;
		std::vector<A> v{ a,b,c,d,e };
		std::cout << std::endl;
		v = { f, g };
		std::cout << std::endl;
	}

	std::cin.get();
}
void problem1()
{
	std::allocator<int> alloc;
	auto p1 = alloc.allocate(5);
	auto p2 = p1 + 5;
	std::cout << p1 << " " << p2 << std::endl;
	for (size_t i = 0; i < 5; ++i)
	{
		alloc.construct(p1 + i, i);
	}
	p2 = alloc.allocate(5);
	for (size_t i = 0; i < 5; ++i)
	{
		alloc.construct(p2 + i, i);
	}
	for (auto i = 0; i < 10; ++i)
	{
		std::cout << *(p1 + i) << " ";
	}
	std::cout << std::endl;
	for (auto i = 0; i < 5; ++i)
	{
		std::cout << *(p2 + i) << " ";
	}
	std::cin.get();
}
template<typename Ty>
void print(Ty t)
{
	for (auto i : t)
	{
		std::cout << i << " ";
	}
}
// allocator
//std::allocator<int> alloc;
//auto p = alloc.allocate(6);
//for (size_t i = 0; i < 5; ++i)
//{
//	alloc.construct(p + i, i);
//}
//alloc.construct(p + 5, 5);
//alloc.construct(p + 6, 6);
//for (size_t i = 0; i < 7; ++i)
//{
//	std::cout << *(p + i) << " ";
//}
#include<type_traits>
using namespace std;
namespace sp 
{
	template<bool B, typename T = void>
	struct enable_if {};
	template<typename T>
	struct enable_if <true, T> { using type = T; };
}
template<typename T,
	typename enable_if<is_integral<T>::value, int>::type n = 0>
	void what_am_i(T)
{
	cout << "Integral number" << endl;
}
template<typename T,
	typename enable_if<is_floating_point<T>::value, int>::type n =0>
	void what_am_i(T)
{
	cout << "Floating point number" << endl;
}
template<typename T,
	typename enable_if<is_pointer<T>::value, int>::type n = 0>
	void what_am_i(T)
{
	cout << "Pointer" << endl;
}
void what_am_i(...)
{
	cout << "Unknow type" << endl;
}
#include <functional>
function<void(void)> test1()
{
	return []() {cout << "return lambda"; };
}
function<function<void(void)>(void)> test2()
{
	return []() {cout << "return lambda" << endl;
	return []() {cout << "return lambda2"; };
	};
}
class O {
public:
	O() {}
	O(const O&) 
	{
		cout << "copy";
	}
	O(O&&)
	{
		cout << "move";
	}
};
class T {
public:
	O o;
	T() {};
};
#include "list.hpp"
#include <algorithm>
int main()
{
    cout << "helloworld" << endl;
    sp::vector v{1, 2,3,45};
//    sp::vector<int> v(5);
//    v.push_back(1);
//    v.push_back(2);
//    v.push_back(5);
//    v.push_back(4);
    for(sp::vector<int>::iterator i = v.begin(); i != v.end(); ++i)
    {
        std::cout << *i << std::endl;
    }
	sp::list<int> list = { 1,1,1,2,2,3,4,4,5,5,6 };
	//v.erase(v.begin());
	list.unique();
	for (auto &i : list) {
		cout << " " << i;
	}
}