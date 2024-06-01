#include "iostream"
//2.3.2
//2.18
int main() {
	int* val;
	int val1 = 5;
	val = &val1;
	std::cout << "The value of val is " << *val << '\n';
	std::cout << "The address of val is " << val << '\n';
	std::cout << "The value of object directed by ptr is " << val1 << '\n';

	int ival = 1024;
	int* pi = &ival;
	int** ppi = &pi;
	std::cout << "The value of ival is " << ival << '\n';//输出ival值
	std::cout << "The value of *pi is " << *pi << '\n';//输出*pi指针的值
	std::cout << "The value of **ppi is " << &ppi;//输出**ppi指针的地址
}

//2.19
//引用只能被引用一次，不能一个多次引用，只能绑定一次。引用只引用，不是对象
//指针可以被多次指向，可以做逻辑运算。指针是对象，数据类型多种多样，存储十六进制的内存地址

/*
2.20
声明一个整型变量i并定义赋值42
声明一个整型指针*pl并将i的地址赋值给指针*pl
指针*pl自乘*pl（平方）
*/

/*
* 2.21
a：不合法。*dp指针是double，i是int
b：不合法。*ip指针只能接收地址，但i是整数0
c：合法
*/

/*
2.22
if (p)//如果p的地值为0则为false，1则为true
if (*p)//如果*p指针数值为0则为false，1则为true
*/

/*
* 2.23
可以
确定指针p数据类型和对象数据类型是否相同
确定*或&没有遗漏
确定指针指向变量是地址而不是数值
*/

/*
2.24
因为void可以存储任意数据类型对象的地址，int地址赋值给void *p合法
lp非法因为*lp是long数据类型，但是i是整型，数据类型不一样所以不合法
*/

/*
2.3.3
2.25
a:int *ip,i,&r = i;
ip为整型指针，i为变量。&r引用i
b:int i, *ip = 0;
声明一个整型变量i，声明一个整型*ip指针并定义赋值0
c:int *ip,ip2;
声明一个整型指针变量*ip和整型变量ip2
*/