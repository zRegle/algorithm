#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * leetcode 105. Construct Binary Tree from Preorder and Inorder Traversal
 * 给定一棵二叉树的前序遍历和中序遍历, 还原这棵二叉树
 * 例如:
 * preorder = [3,9,20,15,7]
 * inorder = [9,3,15,20,7]
 *  3
 * / \
 * 9  20
 *   /  \
 *  15   7
 *
 * 思路:
 * 每次取前序遍历的头(即父节点), 在中序遍历中找到对应节点, 分成两半, 不断循环
 * 第一次:
 * root = 3, 那么可以分成:
 *   3
 *  /  \
 * 9  15,20,7
 * 第二次:
 * root = 20
 *   3
 *  / \
 * 9  20
 *   /  \
 *  15   7
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return buildTree(0, preorder.size(), 0, inorder.size(), preorder, inorder);
    }

    TreeNode* buildTree(int pre_start, int pre_end, int in_start, int in_end, vector<int>& preorder, vector<int>& inorder) {
        if (pre_start >= pre_end || in_start >= in_end) return nullptr;
        int root_val = preorder[pre_start]; //取头
        auto pos = find(inorder.begin()+in_start, inorder.end()+in_end, root_val);  //在中序遍历中找到对应位置
        int len = pos - inorder.begin() - in_start; //计算长度
        auto root = new TreeNode(root_val);
        //分两半, 递归
        //对应的位置关系画图比较好理解
        auto left = buildTree(pre_start+1, pre_start+1+len, in_start, in_start+len, preorder, inorder);
        auto right = buildTree(pre_start+1+len, pre_end, in_start+1+len, in_end, preorder, inorder);
        root->left = left; root->right = right;
        return root;
    }
};
