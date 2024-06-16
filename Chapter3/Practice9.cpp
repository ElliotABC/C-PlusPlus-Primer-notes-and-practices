//3.2.2
//3.5
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;

int main() {
	string s1, s2;
	string s3;
	while (getline(cin, s1)) {
		while (getline(cin, s2)) {
			s3 = s1 + s2;
			cout << "s3:" << s3 << endl;
		}
	}
}