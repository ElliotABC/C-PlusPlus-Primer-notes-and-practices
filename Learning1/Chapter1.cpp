//#include "iostream"
//int main()	主函数是整个程序里必要的
//{
//	std::cout << "enter two numbers:" << std::endl;
//	int v1 = 0, v2 = 0;
//	std::cin >> v1 >> v2;
//	std::cout << "the sum of " << v1 << " and " << v2 << " is " << v1 + v2 << std::endl;
//	return 0;//0代表true，非0由系统定义，-1代表错误标识
//}

/*
int main()
{
	int num1 = 0, num2 = 0;
	std::cout << "Hello,World" << std::endl;
	std::cout << "Please input two numbers:";
	std::cin >> num1 >> num2;
	std::cout << "The sum of two numbers is " << num1 + num2;
}
*/

/*
int main()
{
	int sum = 0, val = 1;
	while (val <= 10)//如果满足条件一直循环
	{
		sum += val;//等效于sum = sum + val
		++val;//自加1，等效于val= val + 1
	}
	std::cout << "The sum of 1 to 10 in ascend is " << sum;
	return 0;
}
*/

/*
int main()
{
	int sum = 0, inx = 50;
	while (inx >= 50 and inx <= 100)
	{
		sum += inx;
		++inx;
	}
	std::cout << "The sum of number between 50 and 100 in ascend is " << sum;
	return 0;
}
*/

/*
int main()
{
	int sum = 0, inx = 10;
	while (inx <= 10 and inx >=1)
	{
		sum += inx;
		--inx;
	}
	std::cout << "The sum of value between 1 to 10 in descend is " << sum;
	return 0;
}
*/

/*
int main()
{
	int start = 0, end = 0;
	std::cout << "Please in put two intergers to calculate the sum of values between them:";
	std::cin >> start >> end;
	int sum = 0, inx = start;
	while (inx <= end)
	{
		sum += inx;
		++inx;
	}
	std::cout << "The sum of values between " << start << " and " << end << "is" << sum;
}
*/

/*
int main()
{
	int sum = 0;
	for (int val = 1; val <= 10; ++val)
		sum += val;
	std::cout << "The sum of value between 1 and 10 is " << sum << std::endl;
	return 0;
}
*/

/*
* For循环频繁对比条件，减小性能开销，可以简化一部分重复工作
* While循环满足条件才会循环执行
*/

/*
int main()
{
	int sum = 0, value = 0;
	while (std::cin >> value)//需要在输入完整数后输入Ctrl+Z（文件结束符end-of-file EOF）
		sum += value;
	std::cout << "The sum of the values inputed is " << sum << std::endl;
	return 0;
}
*/

/*
int main()
{
	int value = 0;//定义变量
	int inx = 0;
	int upper = 5;
	int sum = 0;
	while (inx <= upper-1)//判断是否超过upper
	{
		std::cin >> value;//输入value
		sum += value;//value加到sum
		inx = inx + 1;//inx自加一
	}
	std::cout << "The sum of these value is " << sum;//输出sum总值
	return 0;//返回值
}
*/

/*
int main()
{
	int currval = 0, val = 0;//currval是正在统计的值（前面的值），val是新值（后来输入的值即为刚输入的值）
	if (std::cin >> currval) {//输入数字
		int cnt = 1;//当前剩余个数
		while (std::cin >> val) {//输入
			if (val == currval)//如果输入的val和currval相同就cnt自加一
				++cnt;
			else {//如果输入val和currval不相同（为不同值），输出cnt剩余个数，更新currval并初始化cnt为1
				std::cout << currval << "occurs" << cnt << "times" << std::endl;
				currval = val;
				cnt = 1;
			}
		}
		std::cout << currval << "occurs" << cnt << "times" << std::endl;//最终输出存在个数
	}
	return 0;
}
*/

//class类就是自定义数据类型，比如可以自定义一个integer1数据类型，和自带的int和real相似
//声明value变量为integer1类型：integer1 value
//可以对integer1数据类型的变量cin，cout，提取头文件（类似iostream）里的数据，=赋值，+加法，-减法，+=复合赋值运算符将一个integer1对象加到另一个对象上

/*
#include "Sales_item.h"//导入Sales_item.h头文件
int main()
{
	Sales_item item1;//定义item1和item2为Sales_item数据类型
	std::cin >> item1;//输入item1（第一组数据）和item2（第二组数据）
	std::cout << item1<< std::endl;//输出item1和item2
	return 0;
}
*/

/*
#include "Sales_item.h"
int main()
{
	Sales_item item1,item2;
	std::cin >> item1 >> item2;
	if (item1.isbn() == item2.isbn()) {
		std::cout << item1 + item2;
		return 0;
	}
	else {
		std::cerr << "Data must refer to same ISBN" << std::endl;
		return -1;
	}
}
*/

//item1.isbn()==item2.isbn()中的item1.isbn()，左侧item1.isbn（）代表调用“名为item1的对象的isbn成员函数，此函数返回item1中保存的ISBN书号”

/*书店程序
#include "Sales_item.h"
int main()
{
	Sales_item total;//保存下一条交易记录的变量
	if (std::cin >> total) {//如果输入第一天交易数据（有输入）
		Sales_item trans;//声明读取的的变量trans的数据类型为Sales_item
		while (std::cin >> trans) {//输入剩余交易记录
			if (total.isbn() == trans.isbn())//第一天和剩余交易数据对比是否相等，如果相等将trans加到total
				total += trans;
			else {//如果不相等，输出total并重置total
				std::cout << total << std::endl;
				total = trans;
			}
		}
		std::cout << total << std::endl;//输出total值
	}
	else {//如果没有任何输入，没有任何销售记录，输出No data？！
		std::cerr << "No data?!" << std::endl;//一个ostream对象，关联到标准错误。写入到ceer的数据一般不缓冲，通常输出错误信息等。Clog缓冲到日志文件，用于存储报告程序的执行信息
		return -1;//返回错误值-1
	}
	return 0;//返回正确值0
}
*/

/*
Conclusion:
本章介绍了足够多的C++语言的知识，以使你能够编译、运行简单的C++程序。
我们看到了如何定义一个 main函数，它是操作系统执行你的程序的调用入口。
我们还看到了如何定义变量，如何进行输入输出，以及如何编写if、for 和while 语句。
本章最后介绍了 C++中最基本的特性----类
在本章中，我们看到了，对于其他人定义的一个类，我们应该如何创建、使用其对象。
在后续章节中，我们将介绍如何定义自己的类。
*/

int main()
{
	return 0;
}