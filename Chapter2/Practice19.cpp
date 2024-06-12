#include <iostream>
struct Sales_data {
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

struct Foo {
	/*此处为空*/
}

int main() {
	return 0;
}

/*结果：1.错误	C2628	“Foo”后面接“int”是非法的(是否忘记了“; ” ? )	Chapter2	E : \VisualStudio\Project\Learning1\Chapter2\Practice19.cpp	11
		2.错误	C3874	“main”的返回类型应为“int”而非“Foo”	Chapter2	E : \VisualStudio\Project\Learning1\Chapter2\Practice19.cpp	11
		3.错误	C2440	“return”: 无法从“int”转换为“Foo”	Chapter2	E:\VisualStudio\Project\Learning1\Chapter2\Practice19.cpp	12		
		4.错误(活动)	E0065	应输入“;”	Chapter2	E:\VisualStudio\Project\Learning1\Chapter2\Practice19.cpp	11
*/
