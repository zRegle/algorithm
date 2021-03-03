/**
 * Leetcode 437. 路径总和 III
 * 给定一个二叉树，它的每个结点都存放着一个整数值。
 * 找出路径和等于给定数值的路径总数。
 * 路径不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。
 * 二叉树不超过1000个节点，且节点数值范围是 [-1000000,1000000] 的整数。
 *
 * 示例：
 * root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8
 *
 *        10
 *       /  \
 *      5   -3
 *     / \    \
 *    3   2   11
 *   / \   \
 *  3  -2   1
 *  返回 3。和等于 8 的路径有:
 *   (1)5 -> 3
 *   (2)5 -> 2 -> 1
 *   (3)-3 -> 11
 */
#include <unordered_map>
using namespace std;

/* 类似leetcode 560  */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int pathSum(TreeNode* root, int sum) {
        preSum[0] = 1; /* 前缀和为0的路径有一条: 不选取任何节点 */
        dfs(root, 0, sum);
        return ans;
    }

private:
    /* key -> 当前路径从根节点到达某个节点时的路径和
     * value -> 这个和出现的次数 */
    unordered_map<int, int> preSum;
    int ans = 0;
    void dfs(TreeNode* root, int cur, int target) {
        if (!root) return;
        cur += root->val;
        /* 假设当前路径存在节点node, 从根节点到达该节点的和为k = cur - target
         * 那么从节点node到curNode的和就是target */
        if (preSum.find(cur - target) != preSum.end())
            ans += preSum[cur - target];
        preSum[cur]++; /* 记录到达当前节点的和 */
        dfs(root->left, cur, target);
        dfs(root->right, cur, target);
        preSum[cur]--; /* 回溯 */
    }
};