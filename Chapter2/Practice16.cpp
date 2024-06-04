#include <iostream>
int main() {
	constexpr int mf = 20;
	constexpr int ab = mf + 1;
	std::cout << "mf is " << mf << ",ab is mf + 1=" << ab;
	return 0;
}

/*
2.4.4
2.32
int null = 0, *p = null;
//不合法，整型指针*p不能被赋值整型变量null的值0.指针只能被常量赋值。例如：const int null = 0,*p = 0


*/