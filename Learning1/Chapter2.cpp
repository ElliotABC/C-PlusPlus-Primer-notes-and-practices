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

*/