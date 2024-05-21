#include "iostream"
int main() {
	std::cout << "a really,really long string literal "
		"that spans two lines" << std::endl;
	//转义序列
	std::cout << '\n';
	std::cout << "\tHi!This statement has one tab\n";
	std::cout << "\t\tThis statement has two tab"<<'\n';
	std::cout << "\t\t\t" << "Next character is " << '\115' << '\n';
	//std::cout<<"\1234"	这个转义序列只会识别前三个八进制数字（123），后面那个4只会当作字符，大多数机器char占8位，会报错
}
