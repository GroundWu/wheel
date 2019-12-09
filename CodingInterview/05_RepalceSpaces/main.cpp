#include<cstdio>
#include<cstring>
// length 为整个数组的容量
void ReplaceSpaces(char str[],int length)
{
    if(str==nullptr && length <=0)
        return;
    int origin_len = 0;
    int num_of_space = 0;
    int i = 0;
    while(str[i]!='\0')
    {
        ++ origin_len;
        if(str[i]==' ')
            ++num_of_space;
        ++i;
    }

    int new_len = origin_len + 2 * num_of_space;
    if(new_len > length)\
        return;\
    // 双指针记录替换的位置
    int p1 = origin_len;
    int p2 = new_len;
    while(p1 >= 0 && p2 > p1)
    {
        if(str[p1] == ' ')
        {
            str[p2--] = '0';
            str[p2--] = '2';
            str[p2--] = '%';
        }
        else
        {
            str[p2--] = str[p1];
        }
        --p1;
    }
}

// ====================测试代码====================
void Test(char* testName, char str[], int length, char expected[])
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    ReplaceSpaces(str, length);

    if(expected == nullptr && str == nullptr)
        printf("passed.\n");
    else if(expected == nullptr && str != nullptr)
        printf("failed.\n");
    else if(strcmp(str, expected) == 0)
        printf("passed.\n");
    else
        printf("failed.\n");
}

// 空格在句子中间
void Test1()
{
    const int length = 100;

    char str[length] = "hello world";
    Test("Test1", str, length, "hello%20world");
}

// 空格在句子开头
void Test2()
{
    const int length = 100;

    char str[length] = " helloworld";
    Test("Test2", str, length, "%20helloworld");
}

// 空格在句子末尾
void Test3()
{
    const int length = 100;

    char str[length] = "helloworld ";
    Test("Test3", str, length, "helloworld%20");
}

// 连续有两个空格
void Test4()
{
    const int length = 100;

    char str[length] = "hello  world";
    Test("Test4", str, length, "hello%20%20world");
}

// 传入nullptr
void Test5()
{
    Test("Test5", nullptr, 0, nullptr);
}

// 传入内容为空的字符串
void Test6()
{
    const int length = 100;

    char str[length] = "";
    Test("Test6", str, length, "");
}

//传入内容为一个空格的字符串
void Test7()
{
    const int length = 100;

    char str[length] = " ";
    Test("Test7", str, length, "%20");
}

// 传入的字符串没有空格
void Test8()
{
    const int length = 100;

    char str[length] = "helloworld";
    Test("Test8", str, length, "helloworld");
}

// 传入的字符串全是空格
void Test9()
{
    const int length = 100;

    char str[length] = "   ";
    Test("Test9", str, length, "%20%20%20");
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
    Test8();
    Test9();

    return 0;
}
