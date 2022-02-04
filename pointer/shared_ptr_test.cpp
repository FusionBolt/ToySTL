#include<iostream>
#include"shared_ptr.h"
#include"weak_ptr.h"
#include"sp_control.h"
#include<memory>
struct Foo {
	Foo() { std::cout << "Foo...\n"; }
	void p() {
		std::cout << "print Foo...\n";
	}
	~Foo() { std::cout << "~Foo...\n"; }
};

struct D {
	void operator()(Foo* p) const {
		std::cout << "Call delete from function object...\n";
		delete p;
	}
};
class T {
public:
	T() {}
	T(const T&r) {
		std::cout << "construct\n";
	}
	T&operator=(const T&r) {
		std::cout << "operator=\n";
		return *this;
	}
};
template<typename T>
class A {
public:
	A():sp(nullptr) {
		std::cout << "123";
	}
	A(int x, int y, T z):a(x),b(y),c(z) {
		std::cout << a << std::endl;
		std::cout << b << std::endl;
		std::cout << c << std::endl;
	}
	int a;
	int b;
	T c;
	Sp::sp_control<int> sp;
	std::shared_ptr<std::shared_ptr<int>> s;
	template<typename Y>
	A(const A<Y>& a)noexcept 
	{
		s = a.s;
	}
	class B {
	private:
		int b = 1;
	};
};
int main()
{
	
	// shared_ptr
	//{
	//	std::cout << "constructor with no managed object\n";
	//	Sp::shared_ptr<Foo> sh1;
	//}

	//{
	//	std::cout << "constructor with object\n";
	//	Sp::shared_ptr<Foo> sh2(new Foo);
	//	Sp::shared_ptr<Foo> sh3(sh2);
	//	std::cout << sh2.use_count() << '\n';
	//	std::cout << sh3.use_count() << '\n';
	//}

	//{
	//	std::cout << "constructor with object and deleter\n";
	//	Sp::shared_ptr<Foo> sh4(new Foo, D());
	//	Sp::shared_ptr<Foo> sh5(new Foo, [](auto p) {
	//		std::cout << "Call delete from lambda...\n";
	//		delete p;
	//	});
	//}

	// weak_ptr
	//Sp::weak_ptr<int> wp1;
	//Sp::weak_ptr<double> wp2 = wp1; error
	std::cin.get();
}