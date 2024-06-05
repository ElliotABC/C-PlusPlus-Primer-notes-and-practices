#include <iostream>
int main() {
	int a = 3, b = 4;
	std::cout << a << '\n';
	std::cout << b << '\n';
	decltype(a) c = a;
	decltype((b))d = a;
	++c;
	++d;
	std::cout << c << '\n';
	std::cout << d << '\n';
	return 0;
}

/*
2.5.3
2.36
a�����ͱ�����ֵΪ3
bҲ�����ͱ�����ֵΪ4
��Ϊa�����ͳ�����decltype��cҲ�����ͳ�����c��ֵΪa��ֵ��3
��Ϊdecltype ((b)),����decltype�Ľ����b���ã�d������Ҳ��b���ã�d����ֵΪa
c�Լ�1��4
d�Լ�1��4

2.37
a�����ͱ�����ֵΪ3
b�����ͱ�����ֵΪ4
decltype��a��c = a��c��int���ͣ�ֵΪ3
decltype��a = b�� d = a��d��int&���ͣ��󶨵�a

2.38
decltypeָ�����Ͳ���Ҫ��ʼֵ����auto����Ҫ��ʼֵ
decltype ������const�����õķ�ʽ�� auto��ͬ��decltype�Ὣ����const�����ñ�������
int i = 0, &r = i;
//��ͬ
auto a = i;
decltype(i) b = i;

//��ͬ d ��һ�� int&
auto c = r;
decltype(r) d = r;
*/