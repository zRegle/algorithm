/* Leetcode 129.求根到叶子节点数字之和
 * 给定一个二叉树，它的每个结点都存放一个 0-9 的数字，每条从根到叶子节点的路径都代表一个数字。
 * 例如，从根到叶子节点路径 1->2->3 代表数字 123。
 * 计算从根到叶子节点生成的所有数字之和。
 * 示例:
 *  输入: [4,9,0,5,1]
 *      4
 *     / \
 *    9   0
 *   / \
 *  5   1
 *  输出: 1026
 *  解释:
 *  从根到叶子节点路径 4->9->5 代表数字 495.
 *  从根到叶子节点路径 4->9->1 代表数字 491.
 *  从根到叶子节点路径 4->0 代表数字 40.
 *  因此，数字总和 = 495 + 491 + 40 = 1026.
 */
#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int sumNumbers(TreeNode* root) {
        if (!root) return 0;
        string tmp;
        int sum = 0;
        dfs(root, tmp, sum);
        return sum;
    }
private:
    void dfs(TreeNode* root, string& tmp, int& sum) {
        char digit = (char)(root->val + '0');
        tmp += digit;
        if (!root->left && !root->right) {
            //到达叶子节点,加到sum里
            sum += atoi(tmp.c_str());
        } else {
            if (root->left) dfs(root->left, tmp, sum);
            if (root->right) dfs(root->right, tmp, sum);
        }
        tmp.pop_back(); //回溯
    }
};