#include "iostream"
int main() {
	std::cout << "a really,really long string literal "
		"that spans two lines" << std::endl;
	//ת������
	std::cout << '\n';
	std::cout << "\tHi!This statement has one tab\n";
	std::cout << "\t\tThis statement has two tab"<<'\n';
	std::cout << "\t\t\t" << "Next character is " << '\115' << '\n';
	//std::cout<<"\1234"	���ת������ֻ��ʶ��ǰ�����˽������֣�123���������Ǹ�4ֻ�ᵱ���ַ������������charռ8λ���ᱨ��
}
