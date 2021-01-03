/* Leetcode 235.二叉搜索树的最近公共祖先
 * 给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。
 * 最近公共祖先的定义为: 
 *   “对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，
 *   满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return root;
        TreeNode* cur = root;
        while (true) {
            if (cur->val > p->val && cur->val > q->val) {
                /* p和q都在cur的左子树 */
                cur = cur->left;
            } else if (cur->val < p->val && cur->val < q->val) {
                /* p和q都在cur的右子树 */
                cur = cur->right;
            } else {
                /* 两种情况:
                 * (1)p和q分别在cur的左右子树中, cur就是最近公共祖先
                 * (2)cur就是p或者q中的某一个, 此时cur也是最近公共祖先
                 */
                break;
            }
        }
        return cur;
    }
};