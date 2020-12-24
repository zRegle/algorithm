#include <iostream>
#include <map>
using namespace std;

/*
 * leetcode 337. House Robber III
 * 有个小偷来到一片小区, 这片小区的房子构成了一棵二叉树, 每个房子里有一定金额
 * 当连续"爆格"两个相连的房子时, 就会触发报警器
 * 求能够在这片小区偷到的最大的金额
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/*
 * 思路一: 暴力递归求解所有可能结果, 返回从当前节点出发能够偷到的最大金额, 取较大值
 * 最终结果: 124个Test Case, 1800+ms擦边通过
 */
class Solution {
public:
    int rob(TreeNode* root) {
        int rob_cur = rob(root, false, 0);
        int not_rob_cur = rob(root, true, 0);
        return max(rob_cur ,not_rob_cur);
    }

    /**
    * @param root 当前节点
    * @param isParentRobbed root的父节点是否被偷了
    * @param total 到root之前, 偷到的最大金额
    * @return 从root出发, 能够偷到的最大金额
    */
    int rob(TreeNode* root, bool isParentRobbed, int total) {
        if (!root) return 0;
        if (isParentRobbed) {
            //当前不能偷
            int left = rob(root->left, false, total);
            int right = rob(root->right, false, total);
            return total + left + right;
        } else {
            //当前偷
            int left = rob(root->left, true, total);
            int right = rob(root->right, true, total);
            int rob_cur = total + root->val + left + right;

            //当前选择不偷
            int _left = rob(root->left, false, total);
            int _right = rob(root->right, false, total);
            int not_rob_cur = total + _left + _right;

            return max(rob_cur ,not_rob_cur);
        }
    }
};

/*
 * 思路二: 
 * 在思路一中, 我们算rob(root)的时候, 我们已经算了一遍rob(root->left->left), rob(root->left->right)
 * 在算rob(root->left)的时候, 我们又算了一遍, 导致算法复杂度大大增加
 * 我们可以利用map存储已经算过的节点来减少时间复杂度
 *
 * 最终结果: 8ms通过
 */
class Solution2 {
public:
    int rob(TreeNode* root) {
        map<TreeNode*, int> m;
        return robSub(root, m);
    }

    int robSub(TreeNode* root, map<TreeNode*, int>& m) {
        if (!root) return 0;
        map<TreeNode*, int>::iterator it;
        if ((it = m.find(root)) != m.end())
            return it->second;
        int val = 0;
        if (root->left)
            val += robSub(root->left->left, m) + robSub(root->left->right, m);  //当前的偷了
        if (root->right)
            val += robSub(root->right->left, m) + robSub(root->right->right, m);    //当前的偷了
        val = max(val + root->val, robSub(root->left, m) + robSub(root->right, m));  //后面那个是当前的选择不偷
        m.insert({root, val});
        return val;
    }
};

/*
 * 思路三:
 * 定义rob(root)返回一对pair, 第一个元素是不偷root的最大金额, 第二个元素是偷了root的最大金额
 *
 * 结果: 8ms
 */
class Solution3 {
    int rob(TreeNode* root) {
        auto res = robSub(root);
        return max(res->first, res->second);
    }

    pair<int, int>* robSub(TreeNode* root) {
        auto res = new pair<int, int>(0, 0);
        if (!root) return res;
        auto left = robSub(root->left);
        auto right = robSub(root->right);
        
        //不偷当前节点, 就可以放心地直接把左右子树中的各自的最大值加起来
        res->first = max(left->first, left->second) + max(right->first, right->second);
        //偷了当前节点, 故等于当前节点的金额加上在不偷左右子树的根节点情况下, 能够得到的金额
        res->second = root->val + left->first + right->first;
        return res;
    }
};