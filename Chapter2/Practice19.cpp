#include <iostream>
struct Sales_data {
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

struct Foo {
	/*�˴�Ϊ��*/
}

int main() {
	return 0;
}

/*�����1.����	C2628	��Foo������ӡ�int���ǷǷ���(�Ƿ������ˡ�; �� ? )	Chapter2	E : \VisualStudio\Project\Learning1\Chapter2\Practice19.cpp	11
		2.����	C3874	��main���ķ�������ӦΪ��int�����ǡ�Foo��	Chapter2	E : \VisualStudio\Project\Learning1\Chapter2\Practice19.cpp	11
		3.����	C2440	��return��: �޷��ӡ�int��ת��Ϊ��Foo��	Chapter2	E:\VisualStudio\Project\Learning1\Chapter2\Practice19.cpp	12		
		4.����(�)	E0065	Ӧ���롰;��	Chapter2	E:\VisualStudio\Project\Learning1\Chapter2\Practice19.cpp	11
*/
