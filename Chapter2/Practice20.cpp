#include <iostream>
struct Sales_data {
	std::string bookno;//����һ��std::string���͵ĳ�Ա����bookno���ࣨclass�����ͳ�Ա
	std::string bookname;
	unsigned units_sold = 0;
	double revenue = 0.0;//����һ��double���͵ĳ�Ա����revenue����ʼ��ֵΪ0.0
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
}