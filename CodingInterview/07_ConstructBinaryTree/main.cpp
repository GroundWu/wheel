#include "ConstructBinaryTree.h"

using namespace std;

int main()
{
    int preOrder[] = {1,2,4,7,3,5,6,8};
    int inOrder[] = {4,7,2,1,5,3,8,6};
    BinaryTreeNode* root = Construct(preOrder,inOrder,8);
    printBinaryTree(root);
    return 0;
}
