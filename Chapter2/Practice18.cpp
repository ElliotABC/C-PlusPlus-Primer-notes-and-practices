#include <iostream>
int main() {
	int a = 3, b = 4;
	std::cout << a << '\n';
	std::cout << b << '\n';
	decltype(a) c = a;
	decltype((b))d = a;
	++c;
	++d;
	std::cout << c << '\n';
	std::cout << d << '\n';
	return 0;
}

/*
2.5.3
2.36
a是整型变量，值为3
b也是整型变量，值为4
因为a是整型常量，decltype，c也是整型常量，c的值为a的值：3
因为decltype ((b)),所以decltype的结果是b引用，d的类型也是b引用，d被赋值为a
c自加1：4
d自加1：4

2.37
a是整型变量，值为3
b是整型变量，值为4
decltype（a）c = a；c是int类型，值为3
decltype（a = b） d = a；d是int&类型，绑定到a

2.38
decltype指定类型不需要初始值，但auto必须要初始值
decltype 处理顶层const和引用的方式与 auto不同，decltype会将顶层const和引用保留起来
int i = 0, &r = i;
//相同
auto a = i;
decltype(i) b = i;

//不同 d 是一个 int&
auto c = r;
decltype(r) d = r;
*/