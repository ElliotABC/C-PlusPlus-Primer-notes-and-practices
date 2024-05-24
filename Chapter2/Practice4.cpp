#include "iostream"
//带符号和不带符号类型相乘，如果a是int但是b是unsigned int，结果视当前机器上int所占位数而定，这个代码结果是4294967294
int main() {
	int a = 1;
	unsigned int b = -1;
	std::cout << a * b;
}