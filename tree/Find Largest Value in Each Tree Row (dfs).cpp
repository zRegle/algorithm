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
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* 弱智题目, bfs解法看另一个文件 */
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        dfs(root, 0);
        return ans;
    }
private:
    vector<int> ans;
    void dfs(TreeNode *root, int level) {
        if (root == nullptr) return;
        if (ans.size() <= level)
            /* 扩大数组 */
            ans.push_back(INT_MIN);
        ans[level] = max(ans[level], root->val);
        level++;
        dfs(root->left, level);
        dfs(root->right, level);
    }
};