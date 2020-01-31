/* Leectode 114.二叉树展开为链表
 * 给定一个二叉树，原地将它展开为链表。
 * 例如，给定二叉树
 *     1 
 *    / \ 
 *   2   5 
 *  / \   \
 * 3   4   6
 * 将其展开为：
 * 1 
 *  \ 
 *   2 
 *    \ 
 *     3 
 *      \ 
 *       4 
 *        \ 
 *         5 
 *          \ 
 *           6
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    void flatten(TreeNode* root) {
        if (!root) return;
        //先保存原来的左右子树
        auto left = root->left, right = root->right;
        //递归处理子树
        flatten(left); flatten(right);
        root->left = nullptr; //左子树指针置空
        root->right = left; //经过处理的左子树变成右子树
        //将经过处理的右子树连接到当前根节点的最右叶子节点上
        auto cur = root;
        while (cur->right) cur = cur->right;
        cur->right = right;
    }
};