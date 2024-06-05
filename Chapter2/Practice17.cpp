#include <iostream>
using namespace std;
int main() {
	int i = 0, & r = i;
	auto a = r;

	const int ci = i, & cr = ci;
	auto b = ci;
	auto c = cr;
	auto d = &i;
	auto e = &ci;

	const auto f = ci;

	auto& g = ci;
	const auto& j = 42;
/*

	cout << a<<'\n';
	a = 42;
	cout << '\n';
	cout << a<< '\n';

	cout << b << '\n';
	b = 42;
	cout << '\n';
	cout << b << '\n';

	cout << c << '\n';
	c = 42;
	cout << '\n';
	cout << c << '\n';

	//cout << d << '\n';
	//d = 42;
	cout << '\n'<<"d is error";

	//cout << e << '\n';
	//e = 42;
	cout << '\n'<<"e is error";

	//cout << g << '\n';
	//g = 42;
	cout << '\n' << "g is error";
*/
//Sample:
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;
	std::cout << d << std::endl;
	std::cout << e << std::endl;
	std::cout << f << std::endl;
	std::cout << g << std::endl;
	std::cout << "--------------" << std::endl;
	a = 42; b = 42; c = 42; //d = 42; e = 42; g = 42;

	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;
	std::cout << d << std::endl;
	std::cout << e << std::endl;
	std::cout << f << std::endl;
	std::cout << g << std::endl;
	return 0;
}

/*
2.5.2
2.33
a是一个整型变量
b是一个整型（忽略掉顶层const）
c是cr，cr是ci的别名，c是整型常量
d是一个const int*，非法
e是引用ci，ci是const int*，非法
g是const int引用，引用都是底层const（所指对象），不能被赋值

*/
