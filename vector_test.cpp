#include"vector.hpp"
#include<iostream>
using namespace sp;
using std::cout;
using std::endl;
template<typename Ty>
void print(const Ty& v)
{
	for (auto begin = v.cbegin(); begin != v.cend(); ++begin)
	{
		cout << *begin << " ";
	}
	cout << endl;
}
void test1()
{
	vector<int> vec;
	if (vec.empty())
		cout << "vec is empty" << endl;

	vector<int> v{ 15,42,83,64,51 };
	cout << "v(" << v.size() << "):" << endl;
	print(v);
	cout << "v capacity:" << v.capacity() << endl;
	cout << "v maxsize:" << v.max_size() << endl;
	cout << "v at 4:" << v.at(4) << endl;
	cout << "v [] 3:" << v[3] << endl;
	cout << "v front:" << v.front() << endl;
	cout << "v back:" << v.back() << endl;

	v.push_back(666);
	cout << "v push_back 666:" << endl;
	print(v);

	v.erase(v.cend() - 2);
	cout << "v erase last value:" << endl;
	print(v);

	v.pop_back();
	cout << "v pop_back:" << endl;
	print(v);

	cout << "v emplace begin:" << endl;
	v.emplace(v.cbegin() + 1, 5);
	print(v);

	v.insert(v.cbegin() + 2, 73);
	cout << "v insert three number:" << endl;
	print(v);

	v.resize(4);
	cout << "v resize 4:" << endl;
	print(v);

	v.clear();
	cout << "v after clear size:" << v.size() << endl;
	cout << "！！！！！！！！！！！！！！！" << endl;
}
void test2()
{
	vector<int> v(5);
	cout << v.size() << " " << v.capacity() << endl;
	print(v);
	//v.at(5);
	vector<int> v1{ 3,6,8,9,3 };

	cout << "assignment structure" << endl;
	vector<int> v2(v1);
	print(v2);

	cout << "operator=" << endl;
	vector<int> v3{ 5,7,3 };
	v2 = v3;
	print(v2);

	cout << "move structure" << endl;
	vector<int> v4(std::move(v1));
	print(v4);

	cout << "move assignment" << endl;
	v3 = std::move(v4);
	print(v3);
	//print(v4);
	cout << "！！！！！！！！！！！！！！！" << endl;
}
void test3()
{
	vector<int> v{ 7,2,3,4,5 };
	v.reserve(7);
	print(v);
	cout << v.size() << " " << v.capacity();
	v.emplace_back(9);
	print(v);
	v.erase(v.begin() + 1, v.end() - 1);
	print(v);
	v.erase(v.begin(), v.end());
	print(v);
	cout << "！！！！！！！！！！！！！！！" << endl;
}
void test4() // 泌惚頁operator=(vector) 祥氏烏危
{
	{
		vector<int> v1{ 1,2,3 };
		vector<int> v2(std::move(v1));
		print(v2);
		vector<int> v3;
		v3 = std::move(v2);
	}
}
//int main()
//{
//	test1();
//	test2();
//	test3();
//	//test4();
//	std::cin.get();
//}