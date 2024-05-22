#include "iostream"
#include "../Learning1/Sales_item.h"
/*
int main() {
	long int id = 3;
	int c{id}, d = id;//正确，转换执行，丢失了部分值：小数点后面的所有数字
	std::cout << c, d << '/n';
}
*/
int main() {
	int a = 1;
	std::string empty;//把变量empty非显示初始化为一个空串
	Sales_item item;//被默认初始化的Sales_item对象
}
/*
练习2.9
a:int错误，应该去掉int
b:3.14是float不是int，去掉花括号{}
c:去掉= wage，应该放第二行赋值
d：3.14是float不是int，应该改成float i = 3.14；

练习2.10
global_str初始值为0
global_int初始值为0，在函数体之外
local_int初始值没有，在函数内部，报错
local_str初始值为空串
*/

/*
分离式编译
2.2.2练习
定义
声明并定义iy
声明
*/