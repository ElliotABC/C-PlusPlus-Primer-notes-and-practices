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
			size函数：返回string对象的长度（字符的个数）
					输入必须超过80个字符
					返回无符号整型数
			点操作符：.
					使用点操作符指明哪个对象执行了empty或size或其他函数
					!line.empty()
					line.size()
			string::size_type类型
				size函数返回string::size_type类型的值(无符号类型的值)
				size_type在类string中定义
				所有存放string类的size函数返回值的变量，都应该是string::size_type
				auto或decltype推断变量的类型
					auto len = line.size();		//len变量类型为string::size_type
					decltype var = line.size();	//var变量类型为string::size_type
		比较string对象
			比较运算符(大小写敏感)
				相等性运算符：==和！=检查两个string对象相等或不相等
				关系运算符：<、<=、>、>=检查一个string是否小于、小于等于、大于、大于等于另一个string对象
				eg:
				string str = "Hello";
				string phrase = "Hello World";
				string slang = "Hiya";
				//规则1：str小于对象phrase(str长度比phrase小)
				//规则2：slang大于str也大于phrase
		为string对象赋值
			允许把一个对象的值赋给另一个对象
			eg:
			string st1(10,'c'),st2;		//st1内容为cccccccccc；str2是一个空字符串
			st1 = st2	//赋值：用st2副本替换st1的内容，此时st1和st2都是空字符串
		两个string对象相加
			左侧运算对象和右侧运算对象串接
			加法运算符(+)：对string对象使用加法运算符(+)的结果是一个新string对象
			复合赋值运算符(+=)：右侧string对象内容加到左侧string对象的后面
		字面值和string对象相加
			字符串字面值：“hello”只有一个“”和里面的内容
			string对象：可以指定数据类型的变量(用字符串字面值初始化)
			!!!字符串字面值和string是不同的类型!!!
			eg:string s1 = "hello",s2 = "world";
			   string s3 = s1 + ","+ s2 + '\n';
			string对象和字符串字面值和字符值面值混合在一起时，必须确保每个加法运算符(+)两侧运算对象至少有一个string
			eg:
			string s4 = s1 + ",";		//正确：把一个string对象s1和一个字符串字面值“，”相加
			string s5 = "hello" + ",";	//错误：两个运算对象“hello”和“，”都不是string
			//每个加法运算符都有一个运算对象是string
			string s6 = s1 + "," + "world";//正确：s1 + ","是子表达式tmp，s6为tmp + "world"
			string s7 = "hello" + "," + s2;//错误：不能把字面值直接相加，加法运算符(+)两侧字少有一个string

	处理string对象中的字符
		eg：检查string对象是否空白，改大小写，某个特定字符是否出现
		！！！使用cctype头文件！！！
			标准库函数：
			isalnum(c)		当c是字母或数字时为真
			isalpha(c)		当c是字母时为真
			iscntrl(c)		当c是控制字符时为真
			isdigit(c)		当c是数字时为真
			isgraph(c)		当c不是空格但可打印时为真
			islower(c)		当c是小写字母时为真
			isprint(c)		当c是可打印字符时为真(即c是空格或c具有可视形式)
			ispunct(c)		当c是标点符号时为真(即c不是控制字符、数字、字母、可打印空白中的一种)
			isspace(c)		当c是空白时为真(即c是空格、横向制表符、纵向制表符、回车符、换行符、进纸符中的一种)
			isupper(c)		当c是大写字母时为真
			isxdigit(c)		当c是十六进制数字时为真
			tolower(c)		如果c是大写字母, 输出对应的小写字母; 否则原样输出c
			toupper(c)		如果c是小写字母, 输出对应的大写字母; 否则原样输出c
		基于范围的for语句
			范围for(range for)(C++11 Allowed)
				作用：遍历给定序列中的每个元素并对每个值执行某种操作
				for (declaration:expression)
					statement
				expression是对象表示一个序列，declaration定义一个变量用于访问序列中的基础元素
				每次迭代declaration变量会被初始化为expression下一个元素值
				！！！declaration时刻指向下一个值！！！
				1.查找有多长
				2.改变字符串中的字符
					使用引用作为循环控制变量，这个控制变量实际上绑定到序列的每个元素上
					eg：字符串改写成大小写字母
						string s("Hello World!!!");
						//转换成大写形式
						for (auto& c : s)		//对于s中每一个字符
							c = toupper(c);
						cout << s << endl;
				3.只处理一部分字符
					下标
						下标运算符([])
							接受输入参数为string::Size_type类型的值：表示要访问的字符的值，返回值是该位置上字符的引用
							string对象下标从0开始
								eg：
								string s("some string");
								int main() {
									if (!s.empty())
										s[0] = toupper(s[0]);
									cout << s << endl;
								}
								string对象s包含两个字符
									s[0]是第一个字符
									s[1]是第二个字符
									s[s.size()-1]是最后一个字符
					迭代器
						使用下标执行迭代
						eg:
						string s("some string");
						int main() {
							for (decltype(s.size()) index = 0; index != s.size() && !isspace(s[index]); ++index)//逻辑与运算符&&，参与运算的两个运算对象都为真，则逻辑与结果为真：TRUE TRUE ---->TRUE	TRUE FALSE ---->FALSE	FALSE FLASE ---->FALSE
								s[index] = toupper(s[index]);			//只有达到左侧的s.size()后才会执行右侧s[index]
							cout << s << endl;
						}
						使用下标随机访问
							通过计算得到下标值，直接获取对应位置的字符(不用每次都从前往后依次访问)
							eg:
							#include <iostream>
	#include <string>

	using std::cin;
	using std::cout;
	using std::endl;
	using std::string;

	int main() {
		const string hexdigits = "0123456789ABCDEF";
		cout << "Enter a series of numbers between 0 and 15"
			<< " separated by spaces. Hit ENTER when finished:"
			<< endl;
		string result;			//保存十六进制字符串
		string::size_type n;	//保存输入流读取的数
		while (cin>>n)
			if (n<hexdigits.size())
				result += hexdigits[n];
		cout << "Your hex number is:" << result << endl;
	}

	标准库类型vector
		表示对象的集合
		1.所有对象的类型都相同
		2.每个对象都有与之对应的索引-->访问对象
		容器：容纳其他对象
		类模板：编译器生成类或函数编写的一份说明(实例化)
		需要指出编译器把类或函数实例化哪种类型
		eg:
		vector<int> ivec;				//ivec保存int类型的对象
		vector<Sales_item> Sales_vec;	//保存Sales_item类型的对象Sales_vec
		vector<vector<string>> file;	//该向量的元素是vector对象
		//编译器根据模板生成了三种不同类型：vector<int>、vector<Sales_item>、vector<vector<string>>
		
	定义和初始化vector对象
		vector模板控制定义和初始化向量的方法
		！！！初始化vector对象的方法！！！
		vector<T> v1			//v1是一个空vector,它潜在的元素是T类型的,执行默认初始化
		vector<T> v2(v1)		//v2中包含有v1所有元素的副本
		vector<T> v2 = v1		//等价于v2(v1),v2中包含有v1所有元素的副本
		vector<T> v3(n,val)		//v3包含了n个重复的元素,每个元素的值都是val
		vector<T> v4(n)			//v4包含了n个重复地执行了值初始化的对象
		vector<T> v5{a,b,c……}	//v5包含了初始值个数的元素,每个元素被赋予相应的初始值
		vector<T> v5={a,b,c……}//等价于v5{a,b,c ... }
		eg:默认初始化vector对象

*/