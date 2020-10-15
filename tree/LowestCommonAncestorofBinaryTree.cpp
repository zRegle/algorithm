/* Leetcode 236.二叉树的最近公共祖先
 * 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
 */
#include <cstddef>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL) return NULL;
        /* 如果找到p或者q, 返回找到的节点 */
        if (root->val == p->val || root->val == q->val) return root;
        /* 在左子树中寻找p或者q */
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        /* 在右子树中寻找p或者q */
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        if (left == NULL)
            /* 如果p或者q都不在左子树中, 那么必定在右子树中, right就是它们的最近公共祖先 */
            return right;
        if (right == NULL)
            /* 如果p或者q都不在右子树中, 那么必定在左子树中, left就是它们的最近公共祖先 */
            return left;
        /* 如果p和q一个在左子树,一个在右子树, root就是它们的最近公共祖先 */
        return root;
    }
};
/* 因为递归是自底向上返回的, 所以找到的第一个公共祖先就是最近公共祖先 */