/* Leetcode 226.翻转二叉树 */
#include <iostream>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/* 递归 */
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return NULL;
        swap(root->left, root->right);
        (void)invertTree(root->left);
        (void)invertTree(root->right);
        return root;
    }
};

/* 迭代 */
class Solution1 {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return NULL;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            auto node = q.front(); q.pop();
            swap(node->left, node->right);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        return root;
    }
};