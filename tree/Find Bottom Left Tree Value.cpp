/**
 * Leetcode 513. 找树左下角的值
 * 给定一个二叉树，在树的最后一行找到最左边的值。
 * 示例:
 * 输入:
 *       1
 *      / \
 *     2   3
 *    /   / \
 *   4   5   6
 *  /
 * 7
 * 输出: 7
 */
#include <queue>
using std::queue;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* 明显用bfs, 从右往左遍历 */
class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        TreeNode *node;
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                node = q.front(); q.pop();
                if (node->right) q.push(node->right);
                if (node->left) q.push(node->left);
            }
        }
        return node->val;
    }
};