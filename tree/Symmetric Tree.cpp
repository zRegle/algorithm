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

//递归版本
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

//迭代版本
class Solutions2 {
public:
    //层次遍历左右两棵子树
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        queue<TreeNode*> q;
        q.push(root->left); q.push(root->right);
        while (!q.empty()) {
            TreeNode* n1 = q.front(); q.pop();
            TreeNode* n2 = q.front(); q.pop();
            if (!n1 && !n2)
                continue;
            else if (n1 && n2) {
                if (n1->val != n2->val)
                    return false;
                q.push(n1->left); q.push(n2->right);
                q.push(n1->right); q.push(n2->left);
            } else
                return false;
        }
        return true;
    }
};