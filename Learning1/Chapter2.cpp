#include "iostream"
/*
���ͣ������źͲ�������
	�����ţ�int��short��long��long long
	�޷��ţ� unsigned int��unsigned short��unsigned long��unsigned long long
�ַ��ͣ������źͲ�������
	�����ţ�char���ɱ�������������signed char
	�������ţ�char���ɱ�������������unsigned char
�����ͣ�bol
	bol��true or false
��չ�ַ���
*/

/*
int��long��long long��short����
int���������������ͣ����Դ����Ż��߲������ţ���Ҫ��unsigned��
long��һ��ǰ׺������long int��int��Χ���󣬿��Լӵ�ǰ������Χ
long long��long��ͬ���ã�������չ�ķ�Χ��long��������long long int
short��һ��ǰ׺�����ú�long�෴��������С��Χ������short int

�޷��źʹ�������������
�޷��ű�ʾ������������0
�����ű�ʾ���ڵ���0
eg��8bit unsigned char��Χ��0��127
8bit signed char��Χ��-128-127

flout��double����
double��float����ʾС��
double���ȱ�float��
*/

/*
����-��flout������Ҫ�ǳ���ȷ��С����һ��ֻҪС�������λ
����-��flout��ͬ������Ҫ�ǳ���ȷ��С����ֻҪС�������λ
����-��boolean���ж��Ƿ񸶿������return true��û�и���return false
*/

/*
����ת��
�ǲ�����������ֵ��ֵ���������ͣ������ʼֵΪ0�����Ϊfalse��������Ϊtrue
����ֵ��ֵ���ǲ������ͣ���ʼֵΪfalse����Ϊ0����ʼֵΪtrue����Ϊ1
��������ֵ���������ͣ����ƴ���������������С����֮ǰ�Ĳ��֣�ȡ������
������ֵ���������ͣ�С�����ּ�Ϊ0.��������������㷶Χ�����ȿ��ܻ���ʧ
�����������ͳ�����Χ��8bit��unsigned integer�������ֵ-1�������255
���������ͳ�����Χ��δ����
*/
/*
int main() {
	unsigned u1 = 42, u2 = 10;
	std::cout << u2 - u1 << std::endl;//���ȡģ��ֵ
	std::cout << u1 - u2 << std::endl;//���32
}
*/
/*
int main() {
	for (int i = 10; i >= 0; --i)
		std::cout << i << std::endl;
}
*/
/*����ѭ����unsigned integer��-1ʱ�Զ�ת����4294967275
int main() {
	for (unsigned int u = 10; u >= 0; --u)
		std::cout << u << std::endl;
}
*/

/*�����źͲ�������������ˣ����a��int����b��unsigned int������ӵ�ǰ������int��ռλ�������������������4294967294
int main() {
	int a = 1;
	unsigned int b = -1;
	std::cout << a * b;
}
*/

/*
32
4294967263//������4294967264

32
-32
0
0
*/
//������֤
int main() {
	unsigned u = 10, u2 = 42;
	std::cout << u2 - u << std::endl;
	std::cout << u - u2 << std::endl;

	int i = 10, i2 = 42;
	std::cout << i2 - i << std::endl;
	std::cout << i - i2 << std::endl;
	std::cout << i - u << std::endl;
	std::cout << u - i << std::endl;
}

/*
����ֵ��������ֵ����ı䣩��
	����
		�˽��ƣ�0��ͷ-�����ͣ�int��unsigned int,long,unsigned long,long long,unsigned long long�гߴ���С��
		ʮ���ƣ�ʲô������-�����ͣ�int��long��long long�гߴ���С�ģ�int��
		ʮ�����ƣ�0x��0X��ͷ
		shortû������ֵ��ʮ��������ֵ�����Ǹ����������-42�����Ų�����������ֵ�ڣ�����ֻ�Ƕ�����ֵȡ��ֵ
		eg��ʮ���ƣ�20
		�˽��ƣ�024
		ʮ�����ƣ�0x14
	����
		һ��С�����ѧ��������ʾ��ָ����ָ��������E��e��ʾ
		
		eg��3.14159.4.57��9.1��0.��0e0��.001


*/