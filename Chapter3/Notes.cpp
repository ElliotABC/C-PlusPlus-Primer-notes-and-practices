#include <iostream>
#include <string>		//�ɱ䳤�ַ���
#include <vector>		//�ɱ䳤�ļ���
//�����⣺string��vector���������͡����ڷ���string�е��ַ���vector�е�Ԫ��
//�������飺����
//		��׼������
//			string
//			vector

/*
�����ռ�using����
	��1�ַ���
	ʹ��using����(����Ҫר��ǰ׺::)
		using namespace::name		//ʹ��using����

		#include <iostream>			//ֱ�ӷ��������ռ��е�����

		eg��
		#include <iostream>
		using std::cin��			//using��������ʹ������cinʱ���������ռ�std��ȡ����
										���ʹ��cout�������Ļ����
		int main(){
			int i;
			cin>>i;			//��ȷ��cin��std::cin������ͬ
			cout<<i;		//����û�ж�Ӧ��using����
			std::cout<<i;	//��ȷ����ʽ�Ĵ�std��ʹ��cout
			return 0;
		}

	����using����
		ͨ��using����������ʹ�ñ�׼�������(ͷ�ļ���Ҫ����using����)
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
	��2�ַ���
	������Ӧ�ôӲ�����(::)���������ʾ����������Ѱ���Ҳ�����
		std::cinʹ���������������::����ʹ�������ռ�std�е�����cin
	
	
*/