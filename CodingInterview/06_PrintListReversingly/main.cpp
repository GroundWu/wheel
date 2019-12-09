#include <cstdio>
#include "../Untilities/List.h"
#include <stack>
using namespace std;

//题目：输入一个链表的头结点，从尾到头反过来打印每个节点的值
// 栈的方式实现
void PrintReversingly_1(ListNode* pHead)
{
    std::stack<ListNode*> nodes;

    ListNode* pNode = pHead;
    while(pNode!=nullptr)
    {
        nodes.push(pNode);
        pNode = pNode->m_pNext;
    }

    while(!nodes.empty())
    {
        pNode = nodes.top();
        printf("%d\t",pNode->m_nValue);
        nodes.pop();
    }
}
//递归方式
void PrintReversingly_2(ListNode* pHead)
{
        if(pHead!=nullptr)
        {
            PrintReversingly_2(pHead->m_pNext);
            printf("%d\t",pHead->m_nValue);
        }

}

// ====================测试代码====================
void Test(ListNode* pHead)
{
    PrintList(pHead);
    PrintReversingly_1(pHead);
    printf("\n");
    PrintReversingly_2(pHead);
}

void Test1()
{
    printf("\nTest1 begins.\n");

    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNode(pNode1, pNode2);
    ConnectListNode(pNode2, pNode3);
    ConnectListNode(pNode3, pNode4);
    ConnectListNode(pNode4, pNode5);

    Test(pNode1);

    DestroyList(pNode1);
}

// 只有一个结点的链表: 1
void Test2()
{
    printf("\nTest2 begins.\n");

    ListNode* pNode1 = CreateListNode(1);

    Test(pNode1);

    DestroyList(pNode1);
}

// 空链表
void Test3()
{
    printf("\nTest3 begins.\n");

    Test(nullptr);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();

    return 0;
}


