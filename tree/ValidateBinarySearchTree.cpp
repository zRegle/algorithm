#include <stack>
using namespace std;

/*
 * leetcode 98. Validate Binary Search Tree
 * 判断一棵二叉树是否为搜索二叉树
 *
 * 错误做法:
 * bool isValidBST(TreeNode* root) {
    if (!root) return true;
    bool left = true, right = true;
    if (root->left) {
        auto lchild = root->left;
        left = lchild->val < root->val && isValidBST(lchild);
    }
    if (root->right) {
        auto rchild = root->right;
        right = rchild->val > root->val && isValidBST(rchild);
    }
    return left && right;
   }
 * 这样子做只能保证当前节点的左右两个子节点满足二叉搜索树的关系
 * 不能保证子节点与当前节点的父节点的关系, 反例:
 *   10
 *  /  \
 * 7   15
 *    /  \
 *   11   20
 *  / \
 * 5  12
 * 节点5与节点10不满足关系
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


//思路:
//在每一次递归的时候, 传入当前递归的取值范围
//实际上就是把当前节点和父节点以及祖父节点的关系传入进去了
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return isValidBST(root, nullptr, nullptr);
    }

    bool isValidBST(TreeNode* root, TreeNode* min, TreeNode* max) {
        if (root == nullptr) return true;
        if ((min && root->val <= min->val) || (max && root->val >= max->val))
            return false;
        return isValidBST(root->left, min, root) && isValidBST(root->right, root, max);
    }
};

//BST的中序遍历是严格递增的序列, 中序遍历一下就知道
class Solution2 {
public:
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> s;
        TreeNode* cur = root, *prev = nullptr;
        while (!s.empty() || cur) {
            while (cur) {
                s.push(cur);
                cur = cur->left;
            }
            cur = s.top();
            if (prev && prev->val >= cur->val)
                return false;
            prev = cur;
            s.pop();
            cur = cur->right;
        }
        return true;
    }
};