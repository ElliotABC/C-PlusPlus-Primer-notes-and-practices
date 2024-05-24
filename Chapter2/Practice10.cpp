#include "iostream"
extern int a;//声明变量a，extern代表外部来自Practice9里已经声明定义好的的全局变量
int main() {//同一个工程文件里，main函数只需要写一个
	std::cout << a;
	return 0;
}