/**
 * Leetcode 1379. 找出克隆二叉树中的相同节点
 * 给你两棵二叉树，原始树 original 和克隆树 cloned，以及一个位于原始树 original 中的目标节点 target。
 * 其中，克隆树 cloned 是原始树 original 的一个 副本 。
 * 请找出在树 cloned 中，与 target 相同 的节点，并返回对该节点的引用（
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

/* 同时dfs两棵树 */
class Solution {
public:
    TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) {
        if (original == NULL) return NULL;
        if (original == target) return cloned;
        TreeNode *node;
        if ((node = getTargetCopy(original->left, cloned->left, target)) != NULL)
            return node;
        if ((node = getTargetCopy(original->right, cloned->right, target)) != NULL)
            return node;
        return NULL;
    }
};