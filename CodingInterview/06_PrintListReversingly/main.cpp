#include <cstdio>
#include "../Untilities/List.h"
#include <stack>
using namespace std;

//��Ŀ������һ�������ͷ��㣬��β��ͷ��������ӡÿ���ڵ��ֵ
// ջ�ķ�ʽʵ��
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
//�ݹ鷽ʽ
void PrintReversingly_2(ListNode* pHead)
{
        if(pHead!=nullptr)
        {
            PrintReversingly_2(pHead->m_pNext);
            printf("%d\t",pHead->m_nValue);
        }

}

// ====================���Դ���====================
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

// ֻ��һ����������: 1
void Test2()
{
    printf("\nTest2 begins.\n");

    ListNode* pNode1 = CreateListNode(1);

    Test(pNode1);

    DestroyList(pNode1);
}

// ������
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


