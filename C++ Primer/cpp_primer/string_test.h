#include <string>
#include <cctype>
using std::string;
//����ͳ�ʼ��string����
void init_string()
{
    string s1;  //Ĭ�ϳ�ʼ��
    string s2(s1);  //s2��s1�ĸ���
    string s3 = "hiya"; //s3�Ǹ��ַ�������ֵ�ĸ���
    string s4(10,'c');  //s4��ʼ��Ϊ����10��c�ַ���ɵĴ�
}

// string �����ϵĲ���
void string_operation()
{
    string s;
    //��дstring����
    //std::cin>>s;
    //std::cout<<s<<std::endl;

    //��ȡδ֪������string����
    //while(std::cin>>s)
    //    std::cout<<s<<std::endl;

    //ʹ��geline��ȡһ����
    //while(getline(std::cin,s))
    //    std::cout<<s<<std::endl;

    //string��empty��size����
    //while(getline(std::cin,s))
    //    if(s.size()>10)
    //    if(!s.empty())
    //        std::cout<<s<<std::endl;

    // ����ֵ��string�������
    /*
    string s1 = "hello";
    string s2 = "world";
    std::cout<<s1+s2<<std::endl;;
    string s3 = s1+", "+s2+'\n';
    std::cout<<s3;
    //����string s4 = "hello" + ",";
    string s5 = s1+","+"world";
    std::cout<<s5<<std::endl;
    //����string s6 = "hello"+","+world;
    */

    //����string������ַ�
    /*
    string str("some string");
    for(auto c:str)
        std::cout<<c<<std::endl;
    */

    // ͳ��string�����б����ŵĸ���
    s = "Hello World!!!";
    /*
    decltype(s.size()) punct_cnt=0;
    for(auto c:s)
        if(ispunct(c))
            ++punct_cnt;
    std::cout<<punct_cnt<<" punctuation characters in "<<s<<std::endl;
    */

    for(auto &c : s)
        c = toupper(c);
    std::cout<<s<<std::endl;

}
