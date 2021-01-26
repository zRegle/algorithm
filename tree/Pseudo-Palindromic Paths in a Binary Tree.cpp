/**
 * Leetcode 1457. 二叉树中的伪回文路径
 * 给你一棵二叉树，每个节点的值为 1 到 9 。我们称二叉树中的一条路径是 「伪回文」的，当它满足：
 * 路径经过的所有节点值的排列中，存在一个回文序列。
 *
 * 请你返回从根到叶子节点的所有路径中 伪回文 路径的数目。
 *
 * 示例 1：
 *      2
 *     / \
 *    3   1
 *   / \   \
 *  3   1   1
 *  输入：root = [2,3,1,3,1,null,1]
 *  输出：2
 *  解释：上图为给定的二叉树。总共有 3 条从根到叶子的路径：路径 [2,3,3] ，路径 [2,1,1] 和路径 [2,3,1] 。
 *      在这些路径中，只有[2,3,3]和[2,1,1]是伪回文路径，
 *      因为路径 [2,3,3] 存在回文排列 [3,2,3] ，路径 [2,1,1] 存在回文排列 [1,2,1] 。
 *
 * 示例 2：
 *      2
 *     / \
 *    1   1
 *   / \
 *  1   3
 *       \
 *        1
 *  输入：root = [2,1,1,1,3,null,null,null,null,null,1]
 *  输出：1
 *  解释：上图为给定二叉树。总共有 3 条从根到叶子的路径：路径 [2,1,1] ，路径 [2,1,3,1] 和路径 [2,1] 。
 *  这些路径中只有[2,1,1]路径是伪回文路径，因为 [2,1,1] 存在回文排列 [1,2,1] 。
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/**
 * 判断一条路径是否为伪回文的充要条件是: 出现奇数次的数字最多为1
 * 因为数字范围是[1, 9], 我们可以用一个32 bit的int表示
 * 第i个bit(从0开始计数)为1代表数字i在当前路径中出现了奇数次
 * 例如: 0b100100 -> 数字2和数字5出现了奇数次
 */
class Solution {
public:
    int pseudoPalindromicPaths (TreeNode* root) {
        dfs(root, 0);
        return ans;
    }

    void dfs(TreeNode* root, int bitmap) {
        if (root == nullptr) return;
        /* 数字出现了偶数次, 它对应的bit多次异或后为0
         * 数字出现了奇数次, 它对应的bit多次异或后为1
         */
        int next = bitmap ^ (1 << root->val);
        if (!root->left && !root->right)
            /* 叶子节点 */
            if (next == 0 || (next & (next - 1)) == 0)
                /* 伪回文, 要不所有数字都出现偶数次
                 * 要不只有一个数字出现了奇数次
                 * (n & (n-1)用来将最低位的1置零)
                 */
                ans++;
        dfs(root->left, next);
        dfs(root->right, next);
    }

private:
    int ans = 0;
};