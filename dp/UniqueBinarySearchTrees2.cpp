/* leetcode 95
 * 给定一串序列1,2,...,n, 求由此序列构成的所有二叉搜索树
 *
 * Input: 3
 * Output:
 * [
 *   [1,null,3,2],
 *   [3,2,null,1],
 *   [3,1,null,null,2],
 *   [2,1,3],
 *   [1,null,2,null,3]
 * ]
 * Explanation:
 * The above output corresponds to the 5 unique BST's shown below:
 *
 * 1         3     3      2      1
 *  \       /     /      / \      \
 *   3     2     1      1   3      2
 *  /     /       \                 \
 * 2     1         2                 3
 *
 * 思路参考UniqueBinarySearchTree
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        if (n == 0) {
            vector<TreeNode*> v;
            return v;
        }
        return generateTress(1, n);
    }

    vector<TreeNode*> generateTress(int start, int end) {
        vector<TreeNode*> v;
        if (start > end) {
            v.push_back(NULL);
            return v;
        }
        for (int i = start; i <= end; ++i) {
            auto left = generateTress(start, i-1);
            auto right = generateTress(i+1, end);
            for (TreeNode* l : left) {
                for (TreeNode* r : right) {
                    auto root = new TreeNode(i);
                    root->left = l;
                    root->right = r;
                    v.push_back(root);
                }
            }
        }
        return v;
    }
};