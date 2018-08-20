#include <iostream>
using namespace std;

/*
 * leetcode 101. Symmetric Tree
 * 判断一棵二叉树是否为对称二叉树
 * 例如:
 *      1
 *     / \
 *    2   2
 *   / \ / \
 *  3  4 4  3
 *  
 * 思路:
 * 跟判断两棵二叉树类似, 只不过递归时传入的是一棵树的父节点左子树, 另一棵树的父节点的右子树
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        return isSymmetric(root->left, root->right);
    }

    bool isSymmetric(TreeNode* p, TreeNode* q) {
        if (!p && !q) return true;  //两棵空树
        if (!p || !q) return false; //一棵为空, 另一棵不为空
        if (p->val != q->val) return false;
        return isSymmetric(p->left, q->right) && isSymmetric(p->right, q->left);
    }
};
