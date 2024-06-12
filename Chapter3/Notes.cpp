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
	
	
*/