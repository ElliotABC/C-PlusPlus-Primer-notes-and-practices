#include <iostream>

int main()
{
	int a = 10;
	int* p = &a;
	int** pp = &p;
	int*** ppp = &pp;

	std::cout << "***ppp三级指针 == " << ***ppp << std::endl;
	std::cout << "**pp二级指针 == " << **pp << std::endl;
	std::cout << "*p一级指针 == " << *p << std::endl;
	std::cout << "a == " << a << std::endl;

	std::system("pause");
}