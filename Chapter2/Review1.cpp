#include <iostream>
int main() {
	const int value = 5;
	const int* p = &value;
	std::cout << "The address that p pointed:" << p << '\n';
	std::cout << "The address of p itself:" << &p << '\n';
	std::cout << "The value that p pointed:" << *p << '\n';
}