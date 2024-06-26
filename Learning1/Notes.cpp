﻿#include <iostream>//vs导入用“”，vscode导入用<>,vscode不兼容“”，最好用<>
//#include作用：预处理器检测到后，自动把头文件的内容替换#include
//#define:头文件保护符,依赖于预处理变量状态：已定义、未定义。#define把一个名字设为预处理变量
//#ifdef：头文件保护符，检查指定的预处理变量是否已经定义：当变量已定义时为真
//#ifndef：头文件保护符，检查指定的预处理变量是否已经定义：当变量未定义时为真
//#endif：头文件保护符，检查结果是否为真：如果检测到结果为真，执行后续操作直到遇到#endif为止
/*避免重复包含发生：
//非活动预处理块(避免重复包含头文件，一般用在一个头文件a被包含在另一个头文件b里)：
//如果在头文件的开始处，使用 #ifndef 指令检查是否已定义了某个特定的宏（在这个例子中是 SALES_DATA_H）。
//如果没有定义该宏（即这是第一次包含该头文件），则使用 #define 指令定义它，并继续包含头文件的其余部分。
//如果已经定义了该宏（即这不是第一次包含该头文件），则 #ifndef 条件失败，并且头文件的其余部分将不会被包含。
#ifndef SALES_DATA_H
#define SALES_DATA_H
#include <string>
struct Sales_data{
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};
#endif
*/

int main(){
	return 0;
}
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

/*
变量
	每个变量都有数据类型，数据类型决定占用内存空间大小和布局方式和存储范围
	变量可以参与运算
	变量（variable）和对象（object）可以互换使用
		变量更强调的是变量名这个符号的含义，更强调名字与内存的联系，而不必关注这段内存是什么类型，有多少字节长度，只关注这个变量名a对应着某段内存。
		而对象的描述更强调的是内存的类型而不在乎名字，也就是说，从对象的角度去看内存，就需要清楚这段内存的字节长度等信息，而不关注这个对象在代码中是否有一个变量名来引用到这段内存
		————————————————（引用yby4769250对变量和对象的解释）

                            版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。
							原文链接：https://blog.csdn.net/yby4769250/article/details/7377526
	变量定义
		类型说明符+一个或多个变量名
		eg：
		int sum = 0，value，units_sold = 0
		sales_item item;//item变量的数据类型是sales_item,需要导入头文件。Chapter1讲过
		std::string book("0-201-78345-X");//book通过string字面值初始化
		string和iostream都是在std命名空间中定义的，string是一种表示可变长字符序列的数据类型
		string的其中几种初始化方法
			赋值法string variable_name = "test01" ;//直接赋值
			拷贝法string variable_name(length, char);//以length为长度的c的拷贝（即length个c）

术语:何为对象?
C++程序员们在很多场合都会使用对象(object)这个名词。通常情况下,对象是指
一块能存储数据并具有某种类型的内存空间。

一些人仅在与类有关的场景下才使用“对象”这个词。另一些人则已把命名的对象
和未命名的对象区分开来,他们把命名了的对象叫做变量。还有一些人把对象和值区分
开来,其中对象指能被程序修改的数据,而值(value)指只读的数据。
*/

/*
初始值
	对象在创建时获得一个特定的值
		eg:double price = 109.99,discount = price * 0.16;//:price先被定义并赋值,随后被用于初始化discount
		double salePrice = applyDiscount (price, discount);//调用函数applyDiscount,然后用函数的返回值初始化
		初始化不是赋值，是创建变量是赋予其一个初始值
		赋值含义是把当前对象擦除，用新值替代

列表初始化(谨慎使用)
	初始化units_sold的int变量并初始化为0
		int units_sold = 0;
		int units_sold = (0);
		int units_sold(0);
		int units_sold{0};//仅限C++11标准
	int units_sold{0}使用花括号->列表初始化
		缺点：可能会丢失信息
			long double id = 3.1415926536;
			int a{id},b = {id};//错误，转换未执行，可能存在丢失信息的风险
			int c{id},d = id;//正确，转换执行，丢失了部分值：小数点后面的所有数字
默认初始化
	没有指定初值，变量被赋予默认值
	变量类型和变量位置决定初始值是什么
		定义于函数体之外的变量会被初始化为0
		定义于函数体之内的变量不会被初始化
		eg：std::string empty;
		Sales_item item

变量声明和定义关系
	分离式编译
		为了支持分离式编译,C++语言将声明和定义区分开来。声明(declaration)使得名字
		为程序所知,一个文件如果想使用别处定义的名字则必须包含对那个名字的声明。而定义
		(definition)负责创建与夕字关联的实体。
		声明一个变量且不定义它，在变量名前添加extern，不要显示的初始化变量
		！！！变量的定义必须出现在且只能出现在一个文件中,而其他用到该变量的文件必须对其进行声明,却绝对不能重复定义！！！
			extern int i;//声明i而非定义
			int j；//声明并定义j
			extern double pi = 3.1416;//定义而不是声明
			Important！
				变量只能被定义一次，但是可以被多次声明！
				假设文件a，文件b。文件a里需要声明并定义变量time，
				如果要在文件b里使用变量time，则必须声明一次变量time，
				不能再次定义这个变量

标识符
	由字符，数字和下划线组成
		必须由字母或下划线开头，长度没有限制，对大小写敏感
		不能使用C++自带的关键字和操作符替代名，不能连续出现两个_下划线，不能_A下划线之后大写祖母
		函数之外的标识符不能_下划线开头
		eg：int somename,someName,SomeName,SOMENAME,_somename
	变量命名规范：
		1.实际含义
		2.小写字母。eg：index
		3.自定义类名大写字母开头。eg：Sales_item
		4.由多个单词组成应有明显区分。eg：student_loan

名字的作用域
	作用域是程序的一部分，用花括号分隔
		同一个名字在不同的作用域中可能指向不同的实体。
		名字的有效区域始于名字的声明语句,以声明语句所在的作用域末端为结束。
	示例代码：
	int main()//main定义于花括号之外，整个程序范围内都可以使用，拥有全局作用域
	{
		int sum = 0, val = 1;//sum在函数体之内，出了main函数块就无法访问，拥有块作用域
		while (val <= 10)
		{
			sum += val;
			++val;
		}
		std::cout << "The sum of 1 to 10 in ascend is " << sum;
		return 0;
	}

嵌套的作用域
	被包含：内层作用域
	包含：外层作用域
		内层作用域可以访问外层的作用域，内存作用域也可以重新定义外层作用域已有的名字
	局部变量如果覆盖全局变量，但仍然需要全局变量，应该在标识符前加::

复合类型
	基于其他类型定义的类型
	引用和指针
		引用
			为对象起了另一个名字，引用类型引用另一个类型，
			声明符写成&d来定义引用类型，d是声明的变量名
			eg：int ival = 1024;//声明定义一个整型变量ival并赋值2014
				int &refVal = ival;//声明一个整型引用refVal，refVal指向ival
				int &refVal;//引用先初始化再指向（初始化后会把引用和变量初始值绑定）
	引用即别名
		refVal = 2;//2赋给refVal绑定的对象上，实际就是ival
		int ii = refVal//与ii = ival结果相同
		获取引用的值，实际上是获取了与引用绑定的对象的值
	引用的定义
		一条语句可以多个引用，引用标识符必须由&开头。
		引用不能与字面值或者表达式计算结果绑定,必须是一个对象。引用和被引用的数据类型必须相同。
			int i = 1024,i2 = 2048;
			int &r = i,r2 = i2;//i和r绑定，r引用i。i2赋值给r2
*/

/*
	指针：指向的另一种复合类型
		值访问符（输出数值）：*varname
		取地址符（输出引用地址）：&varname
		地址访问：直接指针的名字
		varname为变量名
		对其它对象的间接访问
			本身就是对象，可以对指针赋值或拷贝。在生命周期内可以先后指向几个不同的对象
			不需要在定义时赋初始值
		！！！输出这个变量名作用是输出变量在内存中的地址！！！

		空指针：不指向任何对象。指针值为0是false，1是true
			三种初始化方法：（使用指针前必须初始化，定义了对象后再定义指向它的指针）
			int *p1 = nullptr//nullptr特殊类型字面值，C++11以上。推荐
			int *p2 = 0//赋值为0

			#include "cstdlib"//需要导入cstdlib库
			int *p3 = NULL//NULL预处理变量。不推荐
		void*指针
			void*可以存储任意对象的地址
			不清楚地址中到底是什么类型的对象
*/

/*
复合类型声明：
//i是一个int型的数，p是一个int型指针，r是一个int型引用
int i = 1024,*p = &i,&r = i;
int *p1;
int *p1,p2;//p1指向int的指针，p2是int
int *p1,*p2;//p1和p2都指向int的指针
*/

/*
指向指针的指针
	*个数确定指针级别。**表示指向指针的指针，***表示指向指针的指针的指针
	eg：int ival = 1024;
		int *pi = &ival;//声明*pi指针为int并把ival地址赋值给*pi指针
		int **ppi = &pi;// *pi的地址也就是ival的地址赋值给**ppi指针
*/

/*
指向指针的引用
	不能定义指向引用的指针，只能定义对指针的引用
*/

/*
const引用：把引用绑定到对象上
    对常量的引用，不能用做修改他绑定的对象
    eg：const int a = 15;
            const int &b = a;//b引用a
            r1= 42:；//错误，已经引用不能再赋值
            int &c = a;//错误，int不能喝const int引用
    ！！！引用类型必须与被引用对象类型一致！！！
	例外：初始化常量允许初始值为任意表达式（对被引用对象数据类型没有限制）
        int i = 42; •
        const int &r1 = i;//允许将 const int&绑定到一个普通 int 对象上
        const int &r2 = 42;//正确：r1是一个常量引用
        const int &r3 = rl * 2； // 正确：r3是一个常量引用
        int &r4 = r1 * 2;//错误：r4是一个普通的非常量引用
	！！！指针类型必须与其所指对象的类型相同！！！
	指针和const：指针指向常量或非常量3
		指向常量的值：不能改变所指对象的值
		eg：
		const double pi =3.14;//正确，pi是常量值无法被改变
		double *ptr = &pi;//错误，不能用变量指针指向常量引用
		const double *cptr = &pi//正确，常量指针cptr可以指向常量pi引用
		*cptr = 42;//错误，不能直接给指针赋值

const指针：把*放在const关键词之前说明指针是一个常量，不变的是指针本身的值而不是指向的值
	eg:	int errNum = 0;
		int *const curErr = &errNum;//curErr指向errNum
		const double pi = 3.1415926;
		const double *const pip = &pi;

！！！顶层const：指针本身就是个常量！！！
！！！底层const：指针所指对象是常量！！！
const int *const p3；
第一个const不需要初始化（指针的内容），第二个*const指针常量必须初始化（指针所指对象的值）
指针内容不需要初始化但指向对象必须初始化
例外：整形常量a不能直接改变值，只能通过另一个整形常量指针b赋值给a
区别：int i = 0;
	 int *const p1 = &i;//不能改变p1值，顶层const，指针本身
	 const int ci = 42;//不能改变ci值，顶层const，指针本身
	 const int *p2 = &ci;//可以改变p2值，底层const。整形常量指针p2指向ci引用（指针所指向的对象）
	 const int *const p3 = p2//左边是底层const（指针所指对象），右边是顶层const（指针本身）
	（底层const：	（顶层const：指针本身是常量）
	所指对象是常量）	
	const int &r = ci;//声明引用的const都是底层const。整形常量引用r被赋值为ci，所以必然是对引用所指对象赋值
	顶层const不受影响
	
*/

/*
constexpr和常量表达式
	常量表达式：值不会改变并且在编译过程中就能得到计算结果的表达式（即时）
		字面值->常量表达式->const
		数据类型和初始值决定是否常量表达式：
			const int max_files = 20;		//max_files是常量表达式
			const int limit = max_files + 1;//limit是常量表达式
			int staff_size = 27;			//staff_size不是常量表达式，是变量
			const int sz = get_size();		//sz不是常量表达式。虽然是常量，
											但具体值在运行时才会获取到（赋值为一个函数返回值），
											不是常量表达式（非即时）
	constexpr变量（C++11 Allowed）
		可以验证变量值是否为常量表达式
		声明为constexpr的变量一定是常量，必须用常量表达式初始化
		eg：constexpr int mf = 20;			//20是常量表达式
			constexpr int limit = mf + 1;	//mf + 1是常量表达式
			constexpr int sz = size();		//只有当size()是一个constexpr函数（即时），语句才会正确。
											//如果不是constexpr函数，不是常量表达式，语句错误
*/

/*
字面值类型(Literal type)：声明constexpr时用到的限制后的类型
	简单，值显而易见，容易得到
	字面值类型典型例子：
	1.算术类型（int，double）
	2.引用（&a）	！如果定义成constexpr，初始值必须是存储于某个固定地址中的对象或者nullptr或者0！
	3.指针（*a）	！如果定义成constexpr，初始值必须是存储于某个固定地址中的对象或者nullptr或者0！
	不是字面值类型，也不能被定义成constexpr
	1.Sales_item,IO库（iostream）,string类型

指针和constexpr
在constexpr定义的指针中，constexpr只对指针本身有效，对所指对象无关
const int *p = nummptr;		//p是指向常量的指针
constexpr int *q = nullptr	//q是一个常量指针，
							constexpr所定义的对象：指针*q是顶层const（指针本身是constexpr）
*/

/*
处理类型
	类型别名：同意词->某种类型
	目的：自定义基本数据类型的名字。例如typedef double wages。
	！！！实际上使用wages和使用double相同的（给数据类型设定快捷方式）！！！
	简洁明了，易于理解和使用
	typedef double wages;//wages是double的同义词
	typedef wages base,*p//base是double的同义词，p是doible*的同义词
	C++11 Allowed：别名声明
		using SI = Sales_item;//SI是Sales_item的同义词
			别名	别名
				指针和常量的类型别名
					typedef char *pstring	//使用char和使用指针*pstring相同
					const pstring cstr = 0;	//const pstring相当于const char
					const pstring *ps;		//*ps指针的对象指向char的常量指针
*/

/*
auto类型说明符（C++11 Allowed）
	让编译器分析表达式所属类型（必须有初始值来推断变量的类型）
	忽略顶层const(指针本身)，保留底层const(指针所指对象)。
	如果给初始值绑定一个引用，此时常量就不是顶层常量而是低层常量
		const int ci = i,&cr = ci;
		auto b = ci;	//b是一个整数（ci的顶层const特性被忽略了）
		auto c = cr;	//c是一个整数（cr是ci别名，ci本身是一个顶层const）
		auto d = &i;	//d是一个整型指针（整数地址就是指向整数的指针）
		auto e = &ci;	//e是一个指向整数常量的指针（对常量对象取地址是一种低层const）
	是顶层const
		const auto f = ci；	//如果ci的推演类型是int，f则是const int
	引用类型为auto
		auto &g = ci;		//g是一个整型常量引用，绑定到ci
		auto &h = 42;		//错误：不能为为非常量（变量）引用绑定字面值
		const auto &j = 42;	//正确：可以为常量引用绑定字面值
	必须有初始值：
		auto item = val1 + val2;//item初始化为val1和val2相加的结果
		eg：val1是int，val2是int，那么item为int
		val1是double，val2是double，那么item也是double
		val1是Sales_item,val2是Sales_item,那么item也是Sales_item
	可以一个语句声明多个变量：
		auto i = 0,*p = &i;		//正确，i是整数，*p是整型指针，指向i的引用
		auto sz = 0,pi = 3.14;	//错误：sz为整型，pi是double，sz和pi数据类型不一致

	复合类型、常量和auto
		有时候auto推断出来的和初始值不完全一样
		！！！如果引用被当作auto变量的初始值时，真正参与初始化的是引用对象的值
		---->>引用对象的类型作为auto的类型
			eg：int i = 0,&r = i;//r引用变量i，变量i初始值为整数0
				auto a = r;//a被赋值引用r，a是一个整数
	eg：auto k = ci,&l - i;		//k是整数，l是整型引用
		auto &m = ci,*p = &ci;	//m是对整型常量的引用，p是指向整型常量的指针
		auto &n i,*p2 = &ci;	//错误：i数据类型为int，而&ci数据类型为const int，不能用auto
*/

/*
decltype类型指示符(C++11 Allowed)
	让编译器分析表达式所属类型（不需要初始值来推断变量的类型）
	不需要表达式的值初始化。分析表达式并得到类型，不计算实际值
	表达式是变量不需要初始化
	表达式是引用或指针必须初始化
		decltype(f()) sum = x;	//sum的类型就是函数f返回类型
	处理顶层const：
		表达式是变量，返回该变量的类型（包括顶层const和引用）
			const int ci = 0,&cj = ci;
			decltype(ci) x = 0;		//x的类型是const int
			delctype(cj) y = x;		//cj引用是ci，ci是const int，y是const int，y绑定到变量x
			delctype(cj) z;			//错误，z是一个引用，必须初始化
		表达式不是变量，返回表达式结果对应的类型
			//decltype的结果可以是引用类型
			int i = 42,*p = &i,&r = i;
			decltype(r + 0) b;//正确，r+0的结果是int，所以b是一个未初始化的int
			decltype(*p) c;	//错误：c是int&，必须初始化、
	decltype使用不加括号变量，结果：该变量的类型
	decltype使用一层或多层括号，编译器当作表达式，得到引用类型
		decltype ((a))双层括号a的结果必定是引用
		decltype (b)单层括号里b是变量的话结果不是引用，b是引用的话结果必定是引用
		eg：decltype((i)) d;	//错误：((i))是引用i，所以d是int&，必须初始化
			decltype(i) e;		//正确：（i）是引用，e是一个未初始化的int
*/

/*
struct自定义数据类型
	数据类型：一组相关的数据元素组织在一起，使用他们的策略和方法
		eg：Sales_item类
			把ISBN编号、售出量和销售收入等数据组织在一起
			提供isbn函数、>>、<<、+、+=等运算操作
			Sales_item类就是一个数据结构
			istream
			ostream
			string
			……
定义Sales_data类型
	示例：
	struct Sales_data {
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
	};//！！！必须在结束的花括号后加分号；因为后面可以加变量名表示对该对象的定义！！！
	Sales_data accum,trans,*salesptr;

	struct关键词定义Sales_data自定义类型
	紧接类名Sales_data和类体（花括号包围，可以为空）
	与内部必须唯一，与外部可以重复
类数据成员
	数据成员定义了类的对象的具体内容
	每个对象都有自己的一份数据成员拷贝，修改一个对象的数据成员不会影响其他Sales_data的对象
	定义类数据成员方法和定义平台变量相同

	类内初始值(C++11 Allowed)
		类内初始值可以在创建对象的时候初始化数据成员->没有初始值的数据成员会被默认初始化
*/

//类通常被定义在头文件里：
//		eg：string.h		iostream.h			Sales_data.h

/*
使用Sales_data类
	In Practice20.cpp，Practice21.cpp
*/

//代码范例1
/*
Practice20.cpp:代码开始
struct Sales_data {
	std::string bookno;//定义一个std::string类型的成员变量bookno。类（class）类型成员
	std::string bookname;
	unsigned units_sold = 0;
	double revenue = 0.0;//定义一个double类型的成员变量revenue，初始化值为0.0
	double price = 0.0;
};

int main() {
	Sales_data book1;
	book1.bookno = "12345";
	book1.bookname = "Example Book";
	book1.price = 10.99;
	book1.units_sold = 5;
	book1.revenue = book1.units_sold * book1.price;

	std::cout << "Book Name: " << book1.bookname << std::endl;
	std::cout << "Units Sold: " << book1.units_sold << std::endl;
	std::cout << "Revenue: " << book1.revenue << std::endl;
*/

//代码范例2
/*
Practice21.cpp:代码开始
//2.6.2
//2.41
#include <iostream>
#include <string>
#include "E:\VisualStudio\MS_pre_C11\2\Sales_data.h"

struct Sales_item {
	std::string bookno;//定义一个std::string类型的成员变量bookno。类（class）类型成员
	std::string bookname;
	unsigned units_sold = 0;
	double revenue = 0.0;//定义一个double类型的成员变量revenue，初始化值为0.0
	double price = 0.0;
};

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


/*
Conclusion:
类型是C++编程的基础。
类型规定了其对象的存储要求和所能执行的操作。C++语言提供了一套基础内置类
型,如int和char等,这些类型与实现它们的机器硬件密切相关。类型分为非常量和常
量,一个常量对象必须初始化,而且一旦初始化其值就不能再改变。此外,还可以定义复
合类型,如指针和引用等。复合类型的定义以其他类型为基础。
C++语言允许用户以类的形式自定义类型。C++库通过类提供了一套高级抽象类型,
如输入输出和string等。
*/