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
