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

	����string�����е��ַ�
		eg�����string�����Ƿ�հף��Ĵ�Сд��ĳ���ض��ַ��Ƿ����
		������ʹ��cctypeͷ�ļ�������
			��׼�⺯����
			isalnum(c)		��c����ĸ������ʱΪ��
			isalpha(c)		��c����ĸʱΪ��
			iscntrl(c)		��c�ǿ����ַ�ʱΪ��
			isdigit(c)		��c������ʱΪ��
			isgraph(c)		��c���ǿո񵫿ɴ�ӡʱΪ��
			islower(c)		��c��Сд��ĸʱΪ��
			isprint(c)		��c�ǿɴ�ӡ�ַ�ʱΪ��(��c�ǿո��c���п�����ʽ)
			ispunct(c)		��c�Ǳ�����ʱΪ��(��c���ǿ����ַ������֡���ĸ���ɴ�ӡ�հ��е�һ��)
			isspace(c)		��c�ǿհ�ʱΪ��(��c�ǿո񡢺����Ʊ���������Ʊ�����س��������з�����ֽ���е�һ��)
			isupper(c)		��c�Ǵ�д��ĸʱΪ��
			isxdigit(c)		��c��ʮ����������ʱΪ��
			tolower(c)		���c�Ǵ�д��ĸ, �����Ӧ��Сд��ĸ; ����ԭ�����c
			toupper(c)		���c��Сд��ĸ, �����Ӧ�Ĵ�д��ĸ; ����ԭ�����c
		���ڷ�Χ��for���
			��Χfor(range for)(C++11 Allowed)
				���ã��������������е�ÿ��Ԫ�ز���ÿ��ִֵ��ĳ�ֲ���
				for (declaration:expression)
					statement
				expression�Ƕ����ʾһ�����У�declaration����һ���������ڷ��������еĻ���Ԫ��
				ÿ�ε���declaration�����ᱻ��ʼ��Ϊexpression��һ��Ԫ��ֵ
				������declarationʱ��ָ����һ��ֵ������
				1.�����ж೤
				2.�ı��ַ����е��ַ�
					ʹ��������Ϊѭ�����Ʊ�����������Ʊ���ʵ���ϰ󶨵����е�ÿ��Ԫ����
					eg���ַ�����д�ɴ�Сд��ĸ
						string s("Hello World!!!");
						//ת���ɴ�д��ʽ
						for (auto& c : s)		//����s��ÿһ���ַ�
							c = toupper(c);
						cout << s << endl;
				3.ֻ����һ�����ַ�
					�±�
						�±������([])
							�����������Ϊstring::Size_type���͵�ֵ����ʾҪ���ʵ��ַ���ֵ������ֵ�Ǹ�λ�����ַ�������
							string�����±��0��ʼ
								eg��
								string s("some string");
								int main() {
									if (!s.empty())
										s[0] = toupper(s[0]);
									cout << s << endl;
								}
								string����s���������ַ�
									s[0]�ǵ�һ���ַ�
									s[1]�ǵڶ����ַ�
									s[s.size()-1]�����һ���ַ�
					������
						ʹ���±�ִ�е���
						eg:
						string s("some string");
						int main() {
							for (decltype(s.size()) index = 0; index != s.size() && !isspace(s[index]); ++index)//�߼��������&&����������������������Ϊ�棬���߼�����Ϊ�棺TRUE TRUE ---->TRUE	TRUE FALSE ---->FALSE	FALSE FLASE ---->FALSE
								s[index] = toupper(s[index]);			//ֻ�дﵽ����s.size()��Ż�ִ���Ҳ�s[index]
							cout << s << endl;
						}
						ʹ���±��������
							ͨ������õ��±�ֵ��ֱ�ӻ�ȡ��Ӧλ�õ��ַ�(����ÿ�ζ���ǰ�������η���)
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
		string result;			//����ʮ�������ַ���
		string::size_type n;	//������������ȡ����
		while (cin>>n)
			if (n<hexdigits.size())
				result += hexdigits[n];
		cout << "Your hex number is:" << result << endl;
	}

	��׼������vector
		��ʾ����ļ���
		1.���ж�������Ͷ���ͬ
		2.ÿ����������֮��Ӧ������-->���ʶ���
		������������������
		��ģ�壺�����������������д��һ��˵��(ʵ����)
		��Ҫָ���������������ʵ������������
		eg:
		vector<int> ivec;				//ivec����int���͵Ķ���
		vector<Sales_item> Sales_vec;	//����Sales_item���͵Ķ���Sales_vec
		vector<vector<string>> file;	//��������Ԫ����vector����
		//����������ģ�����������ֲ�ͬ���ͣ�vector<int>��vector<Sales_item>��vector<vector<string>>
		
	����ͳ�ʼ��vector����
		vectorģ����ƶ���ͳ�ʼ�������ķ���
		��������ʼ��vector����ķ���������
		vector<T> v1			//v1��һ����vector,��Ǳ�ڵ�Ԫ����T���͵�,ִ��Ĭ�ϳ�ʼ��
		vector<T> v2(v1)		//v2�а�����v1����Ԫ�صĸ���
		vector<T> v2 = v1		//�ȼ���v2(v1),v2�а�����v1����Ԫ�صĸ���
		vector<T> v3(n,val)		//v3������n���ظ���Ԫ��,ÿ��Ԫ�ص�ֵ����val
		vector<T> v4(n)			//v4������n���ظ���ִ����ֵ��ʼ���Ķ���
		vector<T> v5{a,b,c����}	//v5�����˳�ʼֵ������Ԫ��,ÿ��Ԫ�ر�������Ӧ�ĳ�ʼֵ
		vector<T> v5={a,b,c����}//�ȼ���v5{a,b,c ... }
		eg:Ĭ�ϳ�ʼ��vector����

*/