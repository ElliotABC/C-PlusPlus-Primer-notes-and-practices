#include <iostream>
int main() {
	constexpr int mf = 20;
	constexpr int ab = mf + 1;
	std::cout << "mf is " << mf << ",ab is mf + 1=" << ab;
	return 0;
}

/*
2.4.4
2.32
int null = 0, *p = null;
//���Ϸ�������ָ��*p���ܱ���ֵ���ͱ���null��ֵ0.ָ��ֻ�ܱ�������ֵ�����磺const int null = 0,*p = 0


*/