#include <iostream>
#include <vector>
using namespace std;

/*
 * leetcode 199. Binary Tree Right Side View
 * 给定一棵二叉树, 求从右边看这棵二叉树的序列
 *       1            <---
 *      / \
 *     2   3         <---
 *    / \   
 *   5   4         <---
 *  /
 * 6            <---
 * 输出: [1, 3, 4, 6]
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> v;
        if (!root) return v;
        rightSideView(root, v);
        return v;
    }

    void rightSideView(TreeNode* root, vector<int>& v) {
        if (!root) return;
        v.push_back(root->val);
        vector<int> left(v), right(v);  //左右子树各自拷贝一份
        //递归
        rightSideView(root->left, left);
        rightSideView(root->right,right);
        int i = v.size();   //将当前节点往下从右看得到的结果加上
        for (; i < right.size(); ++i) v.push_back(right[i]);    //优先加右边的
        //左子树得出的序列比右子树多, 表明左子树的高度大于右子树, 加上多出的高度对应的那部分
        while (i < left.size()) v.push_back(left[i++]); 
    }
};