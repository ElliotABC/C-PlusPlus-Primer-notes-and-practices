#include <iostream>
int main(){
    double dval = 1.92;
    const int &ri = dval;
    std::cout<<ri<<'\n';//输出ri引用的dval地址
    std::cout<<&ri<<'\n';//输出ri引用的地址
    //实际编译器转换成：
    //const int temp = dval;
    //const int &ri = dval;
    //ri绑定一个临时量对象：暂存表达式结果临时创建的一个对象
    int i = 42;//引用ri绑定对象i
    int &r1 = i;//i2也鄉定对象i，但是不允许通过工r2修改i的值
    const int &r2 = i;
    r1 = 0;//r1并非常量，i的值修改为0
    //r2 = 0;   错误：r2是一个常量引用,常量引用不能修改值
    std::cout<<r1;
}