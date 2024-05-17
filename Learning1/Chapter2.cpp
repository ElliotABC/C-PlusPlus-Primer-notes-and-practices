#include "iostream"
/*
整型：带符号和不带符号
	带符号：int，short，long，long long
	无符号： unsigned int，unsigned short，unsigned long，unsigned long long
字符型：带符号和不带符号
	带符号；char（由编译器决定），signed char
	不带符号：char（由编译器决定），unsigned char
布尔型：bol
	bol：true or false
扩展字符型
*/

/*
int，long，long long和short区别？
int是整数，属于整型，可以带符号或者不带符号（需要加unsigned）
long是一个前缀，例如long int比int范围更大，可以加到前面扩大范围
long long和long相同作用，但是扩展的范围比long更大，例如long long int
short是一个前缀，作用和long相反，可以缩小范围，例如short int

无符号和带符号类型区别？
无符号表示正数，负数和0
带符号表示大于等于0
eg：8bit unsigned char范围：0～127
8bit signed char范围：-128-127

flout和double区别？
double和float都表示小数
double精度比float大
*/

/*
利率-》flout，不需要非常精确的小数，一般只要小数点后两位
本金-》flout，同样不需要非常精确的小数，只要小数点后两位
付款-》boolean，判断是否付款。付款完return true，没有付款return false
*/

/*
类型转换
非布尔类型算数值赋值给布尔类型，如果初始值为0，结果为false，否则结果为true
布尔值赋值给非布尔类型，初始值为false则结果为0，初始值为true则结果为1
浮点数赋值给整数类型，近似处理，保留浮点数中小数点之前的部分（取整数）
整数赋值给浮点类型，小数部分记为0.如果整数超过浮点范围，精度可能会损失
不带符号类型超出范围：8bit的unsigned integer，如果赋值-1，结果是255
带符号类型超出范围：未定义
*/
/*
int main() {
	unsigned u1 = 42, u2 = 10;
	std::cout << u2 - u1 << std::endl;//输出取模的值
	std::cout << u1 - u2 << std::endl;//输出32
}
*/
/*
int main() {
	for (int i = 10; i >= 0; --i)
		std::cout << i << std::endl;
}
*/
/*无限循环：unsigned integer在-1时自动转换成4294967275
int main() {
	for (unsigned int u = 10; u >= 0; --u)
		std::cout << u << std::endl;
}
*/

/*带符号和不带符号类型相乘，如果a是int但是b是unsigned int，结果视当前机器上int所占位数而定，这个代码结果是4294967294
int main() {
	int a = 1;
	unsigned int b = -1;
	std::cout << a * b;
}
*/

/*
32
4294967263//订正：4294967264

32
-32
0
0
*/
//运行验证
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
字面值常量（数值不会改变）：
	整型
		八进制：0开头-》类型：int，unsigned int,long,unsigned long,long long,unsigned long long中尺寸最小的
		十进制：什么都不动-》类型：int，long，long long中尺寸最小的（int）
		十六进制：0x或0X开头
		short没有字面值。十进制字面值不会是负数，如果是-42，负号不包含再字面值内，作用只是对字面值取负值
		eg：十进制：20
		八进制：024
		十六进制：0x14
	浮点
		一个小数或科学计数法表示的指数，指数部分用E或e表示
		
		eg：3.14159.4.57，9.1，0.，0e0，.001


*/