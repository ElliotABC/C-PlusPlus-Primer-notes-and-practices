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
	 
��׼������string���ɱ䳤���ַ�����
	�������stringͷ�ļ�(�������ռ�std��)
	#include <string>
	using std::string;

	����ͳ�ʼ��string����
		string s1;			//Ĭ�ϳ�ʼ����s1��һ�����ַ���
		string s2 = s1;		//������ʼ�����Ҳ��ʼֵ�������½�����s2��s1�ĸ���
		string s2(s1)		//ֱ�ӳ�ʼ��
		string s3 = "hiya";	//������ʼ�����Ҳ��ʼֵ�������½�����s3���ַ�������ֵ�ĸ���
		string s3("hiya")	//ֱ�ӳ�ʼ��
		string s4(10,'c');	//s4��������cccccccccc

		string s4 = string(10,'c');	//s4��ʼֵ��string(10,'c'),string����Ϊ������10���ַ�c
		�ȼ���
		string temp(10,'c');	//temp������cccccccccc
		string s4 = temp;		//��temp������s4
	string�����ϵĲ���
		os<<s			sд�뵽�����os�У�����os
		is>>s			��is��ȡ�ַ�������ֵ��s���ַ����Կհ׷ָ�������is		
		getline(is,s)	��is��ȡһ�и�ֵ��s������is
		s.empty()		sΪ�շ���true������Ϊfalse
		s.size()		����s���ַ��ĸ���
		s[n]			����s�е�n���ַ������ã�λ��n��0��ʼ
		s1+s2			����s1��s2���ӵĽ��
		s1=s2			��s2�������s1ԭ���ַ�
		s1==s2			���s1��s2�����ַ���ȫһ�������������
		s1!=s2			���s1��s2�����ַ���һ���������ǲ����
		<,<=,>,>=		�����ַ����ֵ��е�˳��Ƚ�

		��ȡstring����
			ʹ��IO��������дstring����
			(ֻ���ȡ��һ�������ַ�����һ���հ�Ϊֹ,���Կո�����Hello World�����HelloWorld)
				eg��
				#include <iostream>
				#include <string>
				using std::cin
				using std::cout

				string s1,s2;
				cin>>s1>>s2;
				cout<<s1<<s2<<endl;
		��ȡδ֪������string����
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
		getline��ȡһ���У���������ʱ�Ŀհ׷���
			getline���>>
			һ�������з��ͽ�����ȡ���������ؽ��
			getline�����Ĳ�����1.������
							   2.string����
			eg:using std::cin;
			   using std::cout;
			   using std::endl;
			   using std::string;
			   using std::getline;
			   int main() {
					string line;//ÿ�ζ���һ���У�ֱ���ļ�ĩβ
					while (getline(cin, line))
						cout << line << endl;
			   return 0;
			   }
		string��empty��size����
			empty������string��һ����Ա����������string�����Ƿ�Ϊ�շ���һ����Ӧ�Ĳ���ֵ
					   ��Sales_item���ISBN��Աһ��
			size����������string����ĳ��ȣ��ַ��ĸ�����
					������볬��80���ַ�
					�����޷���������
			���������.
					ʹ�õ������ָ���ĸ�����ִ����empty��size����������
					!line.empty()
					line.size()
			string::size_type����
				size��������string::size_type���͵�ֵ(�޷������͵�ֵ)
				size_type����string�ж���
				���д��string���size��������ֵ�ı�������Ӧ����string::size_type
				auto��decltype�ƶϱ���������
					auto len = line.size();		//len��������Ϊstring::size_type
					decltype var = line.size();	//var��������Ϊstring::size_type
		�Ƚ�string����
			�Ƚ������(��Сд����)
				������������==�ͣ�=�������string������Ȼ����
				��ϵ�������<��<=��>��>=���һ��string�Ƿ�С�ڡ�С�ڵ��ڡ����ڡ����ڵ�����һ��string����
				eg:
				string str = "Hello";
				string phrase = "Hello World";
				string slang = "Hiya";
				//����1��strС�ڶ���phrase(str���ȱ�phraseС)
				//����2��slang����strҲ����phrase
		Ϊstring����ֵ
			�����һ�������ֵ������һ������
			eg:
			string st1(10,'c'),st2;		//st1����Ϊcccccccccc��str2��һ�����ַ���
			st1 = st2	//��ֵ����st2�����滻st1�����ݣ���ʱst1��st2���ǿ��ַ���
		����string�������
			������������Ҳ�������󴮽�
			�ӷ������(+)����string����ʹ�üӷ������(+)�Ľ����һ����string����
			���ϸ�ֵ�����(+=)���Ҳ�string�������ݼӵ����string����ĺ���
		����ֵ��string�������
			�ַ�������ֵ����hello��ֻ��һ�����������������
			string���󣺿���ָ���������͵ı���(���ַ�������ֵ��ʼ��)
			!!!�ַ�������ֵ��string�ǲ�ͬ������!!!
			eg:string s1 = "hello",s2 = "world";
			   string s3 = s1 + ","+ s2 + '\n';
			string������ַ�������ֵ���ַ�ֵ��ֵ�����һ��ʱ������ȷ��ÿ���ӷ������(+)�����������������һ��string
			eg:
			string s4 = s1 + ",";		//��ȷ����һ��string����s1��һ���ַ�������ֵ���������
			string s5 = "hello" + ",";	//���������������hello���͡�����������string
			//ÿ���ӷ����������һ�����������string
			string s6 = s1 + "," + "world";//��ȷ��s1 + ","���ӱ��ʽtmp��s6Ϊtmp + "world"
			string s7 = "hello" + "," + s2;//���󣺲��ܰ�����ֱֵ����ӣ��ӷ������(+)����������һ��string

*/