/**
 * Leetcode 872. 叶子相似的树
 * 请考虑一棵二叉树上所有的叶子，这些叶子的值按从左到右的顺序排列形成一个 叶值序列 。
 *      3
 *    /   \
 *   5     1
 *  / \   / \
 * 6   2 9   8
 *    / \
 *   7   4
 * 举个例子，如上图所示，给定一棵叶值序列为 (6, 7, 4, 9, 8) 的树。
 * 如果有两棵二叉树的叶值序列是相同，那么我们就认为它们是 叶相似 的。
 * 如果给定的两个头结点分别为 root1 和 root2 的树是叶相似的，则返回 true；否则返回 false 。
 */
#include <vector>
using std::vector;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* 弱智题, 直接看代码就行 */
class Solution {
public:
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        vector<int> v1, v2;
        preOrderTraversal(root1, v1);
        preOrderTraversal(root2, v2);
        return v1 == v2; /* vector的'=='进行过重载, 可以直接比较 */
    }

private:
    void preOrderTraversal(TreeNode *root, vector<int>& v) {
        if (!root->left && !root->right) {
            v.push_back(root->val);
            return;
        }
        if (root->left) preOrderTraversal(root->left, v);
        if (root->right) preOrderTraversal(root->right, v);
    }
};