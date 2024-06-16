#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
//3.2.2
//3.4
int main() {
	string s1, s2;
	while (cin >> s1 >> s2) {
		if (s1 == s2)
			cout << "s1 is equal to s2" << endl;
		else
			if (s1 > s2)
				cout << "The s1 is larger than s2:" << s1 << endl;
			else
				if (s1.size() == s2.size())
					cout << "s1 has equal length with s2" << endl;
				else
					if (s1.size() > s2.size())
						cout << "s1 has longer length than s2:" << s1 << endl;
					else
						cout << "s1 has shorter length than s2:" << s2 << endl;
	}
}