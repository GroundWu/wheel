#ifndef CONSTRUCTBINARYTREE_H_INCLUDED
#define CONSTRUCTBINARYTREE_H_INCLUDED

#include <iostream>
#include <queue>
#include <exception>
/**
07
����ĳ��������ǰ���������������Ľ����
�ؽ��ö����������������ǰ������������
���Ľ���ж������ظ�������
**/

// �������ڵ�
struct BinaryTreeNode
{
    int val;
    BinaryTreeNode* left;
    BinaryTreeNode* right;
};

BinaryTreeNode* Construct(int*, int*, int);
BinaryTreeNode* ConstructCore(int*, int*, int*,int*);

//�����ؽ��Ķ������ĸ��ڵ�
BinaryTreeNode* Construct(int* preorder, int* inorder, int length)
{
    if(preorder==nullptr||inorder==nullptr||length<=0)
    {
        return nullptr;
    }
    return ConstructCore(preorder,preorder+length-1,inorder,inorder+length-1);
}

BinaryTreeNode* ConstructCore(int* startPreorder,int* endPreorder,int* startInorder,int* endInorder)
{
    int rootVal = startPreorder[0];
    BinaryTreeNode* root =  new BinaryTreeNode();
    root->val = rootVal;
    root->left=root->right=nullptr;

    if(startPreorder==endPreorder)
    {
        if(startInorder==endInorder && *startPreorder==*startInorder)
            return root;
        else
            return nullptr;
    }

    //������������ҵ����ڵ��ֵ
    int* rootInorder = startInorder;
    while(rootInorder<=endInorder && *rootInorder!=rootVal)
    {
        ++rootInorder;
    }
    // �Ҳ���
    if(rootInorder==endInorder && *rootInorder!=rootVal)
        return nullptr;
    // �ֱ�ݹ鹹����������������

    // Ѱ����Preorder���������ķ�Χ
    int length = rootInorder-startInorder;
    int* leftPreorderEnd = startPreorder + length;
    if(length>0)
    {
        //����������
        root->left = ConstructCore(startPreorder+1,leftPreorderEnd,startInorder,rootInorder-1);
    }
    if(length<endPreorder-startPreorder)
    {
        root->right = ConstructCore(leftPreorderEnd+1,endPreorder,rootInorder+1,endInorder);
    }

    return root;
}

// ������ȱ�����ӡ���������Ľṹ
void printBinaryTree(BinaryTreeNode* root)
{
    BinaryTreeNode* tmp;
    std::queue<BinaryTreeNode*> q;
    q.push(root);
    while(!q.empty())
    {
        tmp = q.front();
        q.pop();
        std::cout<<tmp->val<<' ';
        if(tmp->left!=nullptr)
            q.push(tmp->left);
        if(tmp->right!=nullptr)
            q.push(tmp->right);
    }
}
#endif // CONSTRUCTBINARYTREE_H_INCLUDED
