#include <iostream>
using namespace std;

/* leetcode 110. Balanced Binary Tree
 * 判断一棵二叉树是否为平衡二叉树(每个节点的左右子树树高差不大于1)
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/*
 * 思路1(自顶向下):
 * 首先求左右子树的树高, 然后判断高度差是否大于1, 并进行递归
 * 由于在算高度的时候已经递归了一次, 判断高度差时又递归了一次, 总的复杂度是O(N^2)
 */
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if (root == nullptr) return true;
        int left = depth(root->left);
        int right = depth(root->right);
        return abs(left-right) <= 1 && isBalanced(root->left) && isBalanced(root->right);
    }

    int depth(TreeNode* root) {
        if (root == nullptr) return 0;
        return max(depth(root->left), depth(root->right)) + 1;
    }
};

/*
 * 思路2(自底向上):
 * 在算出左右子树的高度时, 我们可以在当时判断一下高度差是否大于1
 * 如果大于1, 就返回-1, 表示当前节点不平衡; 如果不大于1, 则返回树高, 供下一次判断使用
 * 最终, 我们只需要判断根节点返回的值是否为-1即可
 * 
 * 只递归了一次, 复杂度是O(N)
 */
class Solutions2 {
    bool isBalanced(TreeNode* root) {
        return depth(root) != -1;
    }

    int depth(TreeNode* root) {
        if (root == nullptr) return 0;
        int left = depth(root->left);
        if (left == -1) return -1;
        int right = depth(root->right);
        if (right == -1) return -1;
        if (abs(left-right) > 1) return -1;
        return max(left, right) + 1;
    }
};