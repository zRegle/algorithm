/* Leetcode 95.不同的二叉搜索树2
 * 给定数字n, 生成所有不同的二叉搜索树(存着值1...n)
 * 以值i作为根节点, 一共n个节点的的BST数有:
 * BST(i, n) = BST(1, i-1) * BST(i+1, n)
 */
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        return BST(1, n);
    }
private:
    vector<TreeNode*> BST(int start, int end) {
        vector<TreeNode*> tmp;
        if (start > end) {
            tmp.push_back(NULL);
            return tmp;
        } else {
            for (int i = start; i <= end; i++) {
                auto leftTrees = BST(start, i - 1);
                auto rightTrees = BST(i + 1, end);
                for (TreeNode* left : leftTrees) {
                    for (TreeNode* right : rightTrees) {
                        //两层循环体现乘法
                        TreeNode* root = new TreeNode(i);
                        root->left = left;
                        root->right = right;
                        tmp.push_back(root);
                    }
                }
            }
            return tmp;
        }
    }
};