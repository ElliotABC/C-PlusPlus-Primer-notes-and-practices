//非活动预处理块(避免重复包含头文件，一般用在一个头文件a被包含在另一个头文件b里)：
//如果在头文件的开始处，使用 #ifndef 指令检查是否已定义了某个特定的宏（在这个例子中是 SALES_DATA_H）。
//如果没有定义该宏（即这是第一次包含该头文件），则使用 #define 指令定义它，并继续包含头文件的其余部分。
//如果已经定义了该宏（即这不是第一次包含该头文件），则 #ifndef 条件失败，并且头文件的其余部分将不会被包含。
#ifndef SALES_DATA_H
#define SALES_DATA_H
#include <string>
struct Sales_data {
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};
#endif
