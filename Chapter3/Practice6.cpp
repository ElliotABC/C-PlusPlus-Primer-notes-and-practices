#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() {
	string s1 = "hello,", s2 = "world\n";
	string s3 = s1 + s2;		//s3ÄÚÈİÎªhello,world\n
	s1 += s2;
	cout << "s1:" << s1;
	cout << "s2:" << s2;
	cout << "s3:" << s3;
}