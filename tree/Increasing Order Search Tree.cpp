/**
 * Leetcode 897. 递增顺序查找树
 * 给你一个树，请你 按中序遍历 重新排列树，使树中最左边的结点现在是树的根，
 * 并且每个结点没有左子结点，只有一个右子结点。
 *
 * 示例:
 *       5
 *      / \
 *     3  6
 *    /  / \
 *   2  4  8
 *  /  / \
 * 1  7   9
 * 输出:
 *  1
 *   \
 *    2
 *     \
 *      3
 *       \
 *        4
 *         \
 *          5
 *           \
 *            6
 *             \
 *              7
 *               \
 *                8
 *                 \
 *                  9
 */
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
    TreeNode* increasingBST(TreeNode* root) {
        TreeNode dummy(-1);
        parent = &dummy;
        dfs(root);
        return dummy.right;
    }
private:
    TreeNode *parent;
    void dfs(TreeNode *node) {
        if (node == nullptr) return;
        dfs(node->left);
        /* 遍历完左子树, left child置空 */
        node->left = nullptr;
        parent->right = node;
        parent = node;
        dfs(node->right);
    }
};