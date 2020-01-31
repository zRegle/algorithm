/* Leetcode 124. 二叉树中的最大路径和
 * 给定一个非空二叉树，返回其最大路径和。
 * 本题中，路径被定义为一条从树中任意节点出发，达到任意节点的序列。该路径至少包含一个节点，且不一定经过根节点。
 * 示例 2:
 *  输入: [-10,9,20,null,null,15,7]
 *  -10
 *   / \
 *  9  20
 *    /  \
 *   15   7
 *  输出: 42
 */
#include <climits>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int sum = INT_MIN;

    int maxPathSum(TreeNode* root) {
        if (!root) return 0;
        (void)dfs(root);
        return sum;
    }

    /**
     * @param root 根节点
     * @return 从根节点出发到某个叶子结点的路径最大值
     */
    int dfs(TreeNode* root) {
        if (!root) return 0;
        int left = max(0, dfs(root->left));
        int right = max(0, dfs(root->right));
        sum = max(sum, left + right + root->val);
        return max(left, right) + root->val;
    }
};