#include <string>
#include <cctype>
using std::string;
//定义和初始化string对象
void init_string()
{
    string s1;  //默认初始化
    string s2(s1);  //s2是s1的副本
    string s3 = "hiya"; //s3是该字符串字面值的副本
    string s4(10,'c');  //s4初始化为连续10个c字符组成的串
}

// string 对象上的操作
void string_operation()
{
    string s;
    //读写string对象
    //std::cin>>s;
    //std::cout<<s<<std::endl;

    //读取未知数量的string对象
    //while(std::cin>>s)
    //    std::cout<<s<<std::endl;

    //使用geline读取一整行
    //while(getline(std::cin,s))
    //    std::cout<<s<<std::endl;

    //string的empty和size操作
    //while(getline(std::cin,s))
    //    if(s.size()>10)
    //    if(!s.empty())
    //        std::cout<<s<<std::endl;

    // 字面值和string对象相加
    /*
    string s1 = "hello";
    string s2 = "world";
    std::cout<<s1+s2<<std::endl;;
    string s3 = s1+", "+s2+'\n';
    std::cout<<s3;
    //错误：string s4 = "hello" + ",";
    string s5 = s1+","+"world";
    std::cout<<s5<<std::endl;
    //错误：string s6 = "hello"+","+world;
    */

    //访问string对象的字符
    /*
    string str("some string");
    for(auto c:str)
        std::cout<<c<<std::endl;
    */

    // 统计string对象中标点符号的个数
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
