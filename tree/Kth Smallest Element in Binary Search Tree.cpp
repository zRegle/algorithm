/* Leetcode 230. 二叉搜索树中第K小的元素
 * 给定一个二叉搜索树，编写一个函数 kthSmallest 来查找其中第 k 个最小的元素。
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
};

/* 二叉搜索树的中序遍历是一个递增序列 */
class Solution {
public:
    int ans = -1, cnt = 0;

    int kthSmallest(TreeNode* root, int k) {
        cnt = k;
        inorder(root);
        return ans;
    }

    void inorder(TreeNode* root) {
        if (root) {
            inorder(root->left);
            cnt--;
            if (!cnt) {
                ans = root->val;
                return;
            }
            inorder(root->right);
        }
    }
};