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
	字符char
		单引号
		eg：‘a’
			‘d’
			‘g’
	字符串字面值string（由常量字符构成的数组）
		双引号
		例如“a”，包含单独字符a和另一个空字符‘\0’
		eg：“abcdefg”
			“Hello World”
	转义序列
		无法直接使用不可打印和特殊语义的字符，需要使用转义序列(代表一个字符)
			1.不可打印（nonprintable）的字符
			eg：退格，其他控制字符（没有可视的字符）
			2.特殊语义的字符
			eg：‘’“”？\
		如何使用
			反斜线开始
				换行符		\n
				纵向制表符	\v
				反斜线		\\
				回车符		\r
				横向制表符	\t			输出一个tab
				退格符		\b
				问号		\?
				进纸符		\f
				报警符		\a
				双引号		\"
				单引号		\'
			泛化转义序列
				\x后加1个或者多个十六进制数字
				or
				\后加1个，2个或3个八进制数字
				eg：Latin-1字符集
					\7		响铃
					\0		空字符
					\12		换行符
					\115	字符M十六进制
					\40		空格
					\x4d	字符M八进制
*/

/*
指定字面值类型
	通过添加前缀和后缀，可以改变整型、浮点、字符型字面值的默认类型
	U代表unsigned，L代表long，LL代表long long
	UL	unsigned long
	ULL	unsigned long long
	eg：
	L'a'		宽字符字面值，类型为wchar_t
	u8"hi!"		utf-8字符串字面值（utf-8用8位编码编写一个Unicode字符）
	42ULL		无符号整型字面值，类型为unsigned long long
	1E-3F		单精度浮点型字面值，类型为float
	3.14159L	扩展精度浮点型字面值，类型为long double
*/

/*
布尔字面值和指针字面值
	布尔字面值
		true和false
		eg：bool test = false
			bool state = true
	指针字面值
		nullptr
		！2.3.2第47页！
*/
