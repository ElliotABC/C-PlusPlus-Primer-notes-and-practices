#include <iostream>
using namespace std;
int main() {
	int i = 0, & r = i;
	auto a = r;

	const int ci = i, & cr = ci;
	auto b = ci;
	auto c = cr;
	auto d = &i;
	auto e = &ci;

	const auto f = ci;

	auto& g = ci;
	const auto& j = 42;

	cout << a<<'\n';
	a = 42;
	cout << a;

	cout << b << '\n';
	b = 42;
	cout << b;

	cout << c << '\n';
	c = 42;
	cout << c;

	//cout << d << '\n';
	//d = 42;
	cout << '\n'<<"d is error";

	//cout << e << '\n';
	//e = 42;
	cout << '\n'<<"e is error";

	//cout << g << '\n';
	//g = 42;
	cout << '\n' << "g is error";
	return 0;
}

/*
2.5.2
2.33
a��һ�����ͱ���
b��һ�����ͣ����Ե�����const��
c��cr��cr��ci�ı�����c�����ͳ���
d��һ��const int*���Ƿ�
e������ci��ci��const int*���Ƿ�
g��const int���ã����ö��ǵײ�const����ָ���󣩣����ܱ���ֵ
*/
