#include <iostream>
#include <climits>
using namespace std;

/*
 * leetcode 99. Recover Binary Search Tree
 * 给定一棵二叉搜索树, 其中有两个节点被错误地交换了, 要求还原这棵二叉搜索树
 *
 * 思路:
 * 二叉搜索树的中序遍历出来的串必定是个递增序列, 如果有两个节点被错误地交换, 那么必然有两处降序的地方
 * 例如: (其中6和2被交换)
 *   3
 *  / \
 * 6   5
 *    / \
 *   4   2
 * 中序遍历结果: 6 3 5 4 5 2
 * 两处降序的地方分别为[6,3], [5,2]
 * 只要将第一处降序处的较大节点跟第二处降序处的较小节点交换即可
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


class Solution {
public:
    TreeNode* first;
    TreeNode* second;
    TreeNode* prev; //中序遍历前驱节点

    void recoverTree(TreeNode* root) {
        prev = new TreeNode(INT_MIN);
        traverse(root);
        int tmp = first->val;
        first->val = second->val;
        second->val = tmp;
    }

    //中序遍历
    void traverse(TreeNode* root) {
        if (!root) return;
        traverse(root->left);
        //出现降序, 且第一个节点还没找到, 取较大节点
        if (prev->val >= root->val && !first) first = prev;
        //出现降序, 且第一个节点已找到, 取较小节点
        if (prev->val >= root->val && first) second = root;
        prev = root;
        traverse(root->right);
    }
};

int main() {
    auto n1 = new TreeNode(1), n2 = new TreeNode(3), n3 = new TreeNode(2);
    n1->left = n2; n2->right = n3;
    auto s = new Solution();
    s->recoverTree(n1);
    return 0;
}