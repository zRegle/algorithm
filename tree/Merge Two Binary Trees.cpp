/**
 * Leetcode 617. 合并二叉树
 * 给定两个二叉树，想象当你将它们中的一个覆盖到另一个上时，两个二叉树的一些节点便会重叠。
 * 你需要将他们合并为一个新的二叉树。合并的规则是如果两个节点重叠，
 * 那么将他们的值相加作为节点合并后的新值，否则不为 NULL 的节点将直接作为新二叉树的节点。
 * 
 * 示例 1:
 * 输入: 
 * 	Tree 1          Tree 2                  
 *           1              2                             
 *          / \            / \                            
 *         3   2          1   3                        
 *        /                \   \                      
 *       5                  4   7                  
 * 输出: 
 * 合并后的树:
 * 	     3
 * 	    / \
 * 	   4   5
 * 	  / \   \ 
 * 	 5   4   7
 * 注意: 合并必须从两个树的根节点开始。
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* 规定合并到root1中 */
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if (root1 == nullptr && root2 != nullptr) {
            /* root1为空, root2不为空, 将root2移过来 */
            return root2;
        } else if (root1 != nullptr && root2 != nullptr) {
            /* root1和root2都不为空, 值相加 */
            root1->val += root2->val;
            root1->left = mergeTrees(root1->left, root2->left);
            root1->right = mergeTrees(root1->right, root2->right);
        }
        return root1;
    }
};