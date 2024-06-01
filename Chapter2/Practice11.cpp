#include "iostream"

/*
2.2.3练习
a:int double = 3.14;	不合法，标识符为double，数据类型为int，但赋值是float
b：int _;不合法，函数外不能以下划线开头
c：int catch-22；不合法，-不应该存在
d：int 1_or_2 = 1;不合法，一个标识符不应该出现两个下划线_
e：double Double = 3.14;合法，标识符为Double，数据类型为double，赋值为double
*/

/*
2.3.1练习
2.15
a:int ival = 1.01//不合法，整型但是赋值float
b:int &rvall = 1.01;//不合法，引用和被引用数据类型不同，引用类型的初始值必须是一个对象
c:int &refVal5 = dval;//合法，refVal引用dval
int &rval3;//不合法，有引用符合但是没有被绑定

2.16
a：合法，r2是double
b：不合法，r2和r1数据类型不一样
c:不合法，i和r2引用的d数据类型不一样
d：不合法，r1和d数据类型不一样

2.17
10 10
*/
/*
int main() {
	int* ip1, * ip2;
	int ival = 42;
	int* ip = &ival;
	int main() {
		std::cout << ip1 << '\n' << ip2;
	}
}
*/
/*
int main() {
	int var1;
	char var2[10];
	std::cout << "var1变量的地址";
	std::cout << &var1 << '\n';
	std::cout << "var2变量的地址";
	std::cout << &var2 << "\n";
	

	int var = 20;//实际变量的声明
	int* ip;//指针变量的声明

	ip = &var;//在指针变量ip中存储var的地址

	std::cout << "Vale of var variable:" << var << '\n';//输出var的值
	std::cout << "Address stored in ip variable:" << ip << '\n';//输出指针变量ip中存储的地址
	std::cout << "Value of *ip variable:" << *ip << '\n';//输出指针中地址的值

	return 0;
}
*/

int main() {
	int num1 = 6;
	int* num2;
	num2 = &num1;
	num1 = 0;//覆盖原先num1值
	std::cout << *num2 << '\n';//输出指针变量num2指向的变量num1的值
	std::cout << num2;//输出指针变量num2的地址

}