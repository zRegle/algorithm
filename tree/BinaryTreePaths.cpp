/* Leetcode 257.二叉树的所有路径
 * 给定一个二叉树，返回所有从根节点到叶子节点的路径。
 */
#include <vector>
#include <string>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> paths;
        if (!root) return paths;
        string s = to_string(root->val);
        dfs(root, s, paths);
        return paths;
    }

    void dfs(TreeNode* root, string& s, vector<string>& paths) {
        if (!root->left && !root->right) {
            paths.push_back(s);
            return;
        } else if (root->left && root->right) {
            /* 左右孩子都不为空的时候才复制一份当前路径 */
            string copy = s;
            s += "->" + to_string(root->left->val);
            dfs(root->left, s, paths);
            copy += "->" + to_string(root->right->val);
            dfs(root->right, copy, paths);
        } else if (root->left) {
            s += "->" + to_string(root->left->val);
            dfs(root->left, s, paths);
        } else {
            s += "->" + to_string(root->right->val);
            dfs(root->right, s, paths);
        }
    }
};