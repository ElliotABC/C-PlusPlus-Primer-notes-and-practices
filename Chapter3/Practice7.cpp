#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
//3.2.2
//3.2
/*
int main() {
	string readline;
	while (getline(cin, readline))
		cout << readline<<endl;

}
*/

int main() {
	string readline;
	while (cin >> readline) {
		cout << readline << endl;
	}
}

//3.3
/*
string�ѿո�ǰ��ֿ���һ��ֻ��һ���ַ����ǻ�ȫ�����꣬������ո�
getlineֱ�Ӷ�ȡһ���У������ո�ֱ���������з�����
*/