//2.6.2
//2.41
//����Ԥ�����
#include <iostream>
#include <string>
#include "E:\VisualStudio\MS_pre_C11\2\Sales_data.h"

//(��ѡ)����ü����γ�ϰ��
//�ǻԤ�����(�����ظ�����ͷ�ļ���һ������һ��ͷ�ļ�a����������һ��ͷ�ļ�b��)��
//�����ͷ�ļ��Ŀ�ʼ����ʹ�� #ifndef ָ�����Ƿ��Ѷ�����ĳ���ض��ĺ꣨������������� SALES_DATA_H����
//���û�ж���ú꣨�����ǵ�һ�ΰ�����ͷ�ļ�������ʹ�� #define ָ�����������������ͷ�ļ������ಿ�֡�
//����Ѿ������˸ú꣨���ⲻ�ǵ�һ�ΰ�����ͷ�ļ������� #ifndef ����ʧ�ܣ�����ͷ�ļ������ಿ�ֽ����ᱻ������
#ifndef SALES_DATA_H
#define SALES_DATA_H
#include <string>
struct Sales_data {
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};
#endif

//����struct:Sales_item
struct Sales_item {
	std::string bookno;//����һ��std::string���͵ĳ�Ա����bookno���ࣨclass�����ͳ�Ա
	std::string bookname;
	unsigned units_sold = 0;
	double revenue = 0.0;//����һ��double���͵ĳ�Ա����revenue����ʼ��ֵΪ0.0
	double price = 0.0;
};

//������
int main() {
	Sales_data data1, data2;
	//����data1��data2�Ĵ���
	//���data1��data2��ISBN�Ƿ���ͬ����
	//�����ͬ����data1��data2�ܺ�
	double price = 0;//��ĵ��ۣ����ڼ�����������
	std::cin >> data1.bookNo >> data1.units_sold >> price;//�����1�ʽ��ף�ISBN����������������
	data1.revenue = data1.units_sold * price;//������������

	std::cin >> data2.bookNo >> data2.units_sold >> price; //�����2�ʽ��ף�ISBN����������������
	data2.revenue = data2.units_sold * price;//������������

	if (data1.bookNo == data2.bookNo) {//�ж�data1��data2��ISBN�Ƿ���ͬ
		unsigned totalCut = data1.units_sold + data2.units_sold;//����������
		double totalRevenue = data1.revenue + data2.revenue;//����������
		std::cout << "ISBN:"<<data1.bookNo << '\n' << "TotalCut:" << totalCut << '\n' << "Total Revenue:" << totalRevenue<<'\n';
		//�����ISBN�����������������۶ƽ���۸�

		if (totalCut != 0)
			std::cout << "Average Revenue:" << totalRevenue / totalCut << std::endl;//����������Ϊ0���������
		else
			std::cout << "No Sales!" << std::endl;//Ϊ0�����(No Sales)
		return 0;//��־�ɹ�
	}
	else {//����ͬ��ISBN
		std::cerr << "Data must refer to the same ISBN" << std::endl;//���Data must refer to the same ISBN
		return -1;//��־ʧ��
	}
}

/*
���룺
1
2
3
1
2
3

�����
ISBN:1
TotalCut:4
Total Revenue:12
Average Revenue:3
*/