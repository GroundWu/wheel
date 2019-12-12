#ifndef CONSTRUCTBINARYTREE_H_INCLUDED
#define CONSTRUCTBINARYTREE_H_INCLUDED

#include <iostream>
#include <queue>
#include <exception>
/**
07
输入某二叉树的前序遍历和中序遍历的结果，
重建该二叉树，假设输入的前序遍历和中序遍
历的结果中都不含重复的数字
**/

// 二叉树节点
struct BinaryTreeNode
{
    int val;
    BinaryTreeNode* left;
    BinaryTreeNode* right;
};

BinaryTreeNode* Construct(int*, int*, int);
BinaryTreeNode* ConstructCore(int*, int*, int*,int*);

//返回重建的二叉树的根节点
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

    //在中序遍历中找到根节点的值
    int* rootInorder = startInorder;
    while(rootInorder<=endInorder && *rootInorder!=rootVal)
    {
        ++rootInorder;
    }
    // 找不到
    if(rootInorder==endInorder && *rootInorder!=rootVal)
        return nullptr;
    // 分别递归构建左子树和右子树

    // 寻找在Preorder中左子树的范围
    int length = rootInorder-startInorder;
    int* leftPreorderEnd = startPreorder + length;
    if(length>0)
    {
        //构建左子树
        root->left = ConstructCore(startPreorder+1,leftPreorderEnd,startInorder,rootInorder-1);
    }
    if(length<endPreorder-startPreorder)
    {
        root->right = ConstructCore(leftPreorderEnd+1,endPreorder,rootInorder+1,endInorder);
    }

    return root;
}

// 宽度优先遍历打印出二叉树的结构
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
