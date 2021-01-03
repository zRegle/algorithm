#include <iostream>
#include <vector>
using namespace std;

/* leetcode 113. Path Sum II
 * 给定一棵二叉树, 求出所有从根节点到叶子节点的值加起来等于某个数字的路径
 * Given the below binary tree and sum = 22,
 *       _5
 *      / \
 *    _4   _8
 *    /   / \
 *  _11  13 _4
 *  /  \    / \
 * 7   _2  _5   1
 * (数字前带'_'的是符合要求的路径)
 * 输出:
 * [
 *  [5,4,11,2],
 *  [5,8,4,5]
 * ]
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<vector<int>> paths;

    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        if (!root) return paths;
        vector<int> v;
        pathSum(root, v, sum);
        return paths;
    }

    void pathSum(TreeNode* root, vector<int>& v, int sum) {
        if (!root) return;
        v.push_back(root->val);
        //到叶子节点了, 加起来等于sum
        if (!root->left && !root->right && sum == root->val) {
            paths.push_back(v);
        } else {
            //递归调用左右子树
            pathSum(root->left, v, sum-root->val);
            pathSum(root->right, v, sum-root->val);
        }
        //恢复辅助数组
        v.pop_back();
    }
};