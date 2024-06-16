#include <iostream>
#include<string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;

int main() {
	string line;
	while (getline(cin, line)) {
		if (line.size() > 80)
			cout << line << endl;
	}
}