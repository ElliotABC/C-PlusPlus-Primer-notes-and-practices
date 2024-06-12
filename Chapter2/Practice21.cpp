//2.6.2
//2.41
//正常预处理块
#include <iostream>
#include <string>
#include "E:\VisualStudio\MS_pre_C11\2\Sales_data.h"

//(可选)：最好加上形成习惯
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

//定义struct:Sales_item
struct Sales_item {
	std::string bookno;//定义一个std::string类型的成员变量bookno。类（class）类型成员
	std::string bookname;
	unsigned units_sold = 0;
	double revenue = 0.0;//定义一个double类型的成员变量revenue，初始化值为0.0
	double price = 0.0;
};

//主程序
int main() {
	Sales_data data1, data2;
	//读入data1，data2的代码
	//检查data1和data2的ISBN是否相同代码
	//如果相同，求data1和data2总和
	double price = 0;//书的单价，用于计算销售收入
	std::cin >> data1.bookNo >> data1.units_sold >> price;//读入第1笔交易：ISBN、销售数量，单价
	data1.revenue = data1.units_sold * price;//计算销售收入

	std::cin >> data2.bookNo >> data2.units_sold >> price; //读入第2笔交易：ISBN、销售数量，单价
	data2.revenue = data2.units_sold * price;//计算销售收入

	if (data1.bookNo == data2.bookNo) {//判断data1和data2的ISBN是否相同
		unsigned totalCut = data1.units_sold + data2.units_sold;//计算总销量
		double totalRevenue = data1.revenue + data2.revenue;//计算总收入
		std::cout << "ISBN:"<<data1.bookNo << '\n' << "TotalCut:" << totalCut << '\n' << "Total Revenue:" << totalRevenue<<'\n';
		//输出：ISBN、总销售量、总销售额、平均价格

		if (totalCut != 0)
			std::cout << "Average Revenue:" << totalRevenue / totalCut << std::endl;//总销售量不为0则输出单价
		else
			std::cout << "No Sales!" << std::endl;//为0则输出(No Sales)
		return 0;//标志成功
	}
	else {//不相同的ISBN
		std::cerr << "Data must refer to the same ISBN" << std::endl;//输出Data must refer to the same ISBN
		return -1;//标志失败
	}
}

/*
输入：
1
2
3
1
2
3

输出：
ISBN:1
TotalCut:4
Total Revenue:12
Average Revenue:3
*/