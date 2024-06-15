#include <iostream>
#include <string>		//可变长字符串
#include <vector>		//可变长的集合
//迭代库：string和vector的配套类型。用于访问string中的字符或vector中的元素
//内置数组：抽象
//		标准库类型
//			string
//			vector

/*
命名空间using声明
	第1种方法
	使用using声明(不需要专门前缀::)
		using namespace::name		//使用using声明

		#include <iostream>			//直接访问命名空间中的名字

		eg：
		#include <iostream>
		using std::cin；			//using声明，当使用名字cin时，从命名空间std获取它。
										如果使用cout和其他的会错误
		int main(){
			int i;
			cin>>i;			//正确，cin和std::cin含义相同
			cout<<i;		//错误，没有对应的using声明
			std::cout<<i;	//正确，显式的从std中使用cout
			return 0;
		}

	独立using声明
		通过using声明，可以使用标准库的名字(头文件不要包含using声明)
			#include <iostream>
			using std::cin;
			using std::cout;
			using std::endl;
			int main(){
				cout <<"Enter two numbers:"<<endl;
				int v1,v2;
				cin>>v1>>v2;
				cout<<"The sum of "<<v1<<" and "<<v2<<" is "<<v1+v2<<endl;
				return 0;
			}
	第2种方法
	编译器应该从操作符(::)左侧名字所示的作用域中寻找右侧名字
		std::cin使用作用域操作符（::）：使用命名空间std中的名字cin
	 
标准库类型string：可变长的字符序列
	必须包含string头文件(在命名空间std中)
	#include <string>
	using std::string;

	定义和初始化string对象
		string s1;			//默认初始化，s1是一个空字符串
		string s2 = s1;		//拷贝初始化，右侧初始值拷贝到新建对象。s2是s1的副本
		string s2(s1)		//直接初始化
		string s3 = "hiya";	//拷贝初始化，右侧初始值拷贝到新建对象。s3是字符串字面值的副本
		string s3("hiya")	//直接初始化
		string s4(10,'c');	//s4的内容是cccccccccc

		string s4 = string(10,'c');	//s4初始值是string(10,'c'),string对象为用数字10和字符c
		等价于
		string temp(10,'c');	//temp内容是cccccccccc
		string s4 = temp;		//将temp拷贝给s4
	string对象上的操作
		os<<s			s写入到输出流os中，返回os
		is>>s			从is读取字符串并赋值给s，字符串以空白分隔，返回is		
		getline(is,s)	从is读取一行赋值给s，返回is
		s.empty()		s为空返回true，否则为false
		s.size()		返回s中字符的个数
		s[n]			返回s中第n个字符的引用，位置n从0开始
		s1+s2			返回s1和s2连接的结果
		s1=s2			用s2副本替代s1原来字符
		s1==s2			如果s1和s2所含字符完全一样，则他们相等
		s1!=s2			如果s1和s2所含字符不一样，则他们不相等
		<,<=,>,>=		利用字符在字典中的顺序比较

		读取string对象
			使用IO操作符读写string对象
			(只会读取第一个真正字符到下一处空白为止,忽略空格：输入Hello World，输出HelloWorld)
				eg：
				#include <iostream>
				#include <string>
				using std::cin
				using std::cout

				string s1,s2;
				cin>>s1>>s2;
				cout<<s1<<s2<<endl;
		读取未知数量的string对象
			eg:
			#include <iostream>
			#include <string>
			using std::cin;
			using std::cout;
			using std::string;
			using std::endl;
			int main() {
				string word;
				while (cin >> word)
					cout << word << endl;
				return 0;
			}
		getline读取一整行（保留输入时的空白符）
			getline替代>>
			一遇到换行符就结束读取操作并返回结果
			getline函数的参数：1.输入流
							   2.string对象
			eg:using std::cin;
			   using std::cout;
			   using std::endl;
			   using std::string;
			   using std::getline;
			   int main() {
					string line;//每次读入一整行，直到文件末尾
					while (getline(cin, line))
						cout << line << endl;
			   return 0;
			   }
		string的empty和size操作
			empty函数：string的一个成员函数。根据string对象是否为空返回一个对应的布尔值
					   和Sales_item类的ISBN成员一样
*/