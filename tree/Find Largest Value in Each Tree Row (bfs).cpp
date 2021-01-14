/**
 * Leetcode 515. 在每个树行中找最大值
 * 您需要在二叉树的每一行中找到最大的值。
 * 示例：
 * 输入: 
 *           1
 *          / \
 *         3   2
 *        / \   \  
 *       5   3   9 
 * 输出: [1, 3, 9]
 */
#include <climits>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* 弱智题目, dfs解法看另一个文件 */
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        vector<int> ans;
        if (root == nullptr) return ans;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            int maxVal = INT_MIN;
            while (size--) {
                TreeNode *node = q.front(); q.pop();
                maxVal = max(node->val, maxVal);
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            ans.push_back(maxVal);
        }
        return ans;
    }
};