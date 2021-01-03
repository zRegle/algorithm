/**
 * Leetcode 971. 翻转二叉树以匹配先序遍历
 * 给定一个有 N 个节点的二叉树，每个节点都有一个不同于其他节点且处于 {1, ..., N} 中的值。
 * 通过交换节点的左子节点和右子节点，可以翻转该二叉树中的节点。
 * 考虑从根节点开始的先序遍历报告的 N 值序列。将这一 N 值序列称为树的行程。
 * （回想一下，节点的先序遍历意味着我们报告当前节点的值，然后先序遍历左子节点，再先序遍历右子节点。）
 * 我们的目标是翻转最少的树中节点，以便树的行程与给定的行程 voyage 相匹配。
 * 如果可以，则返回翻转的所有节点的值的列表。你可以按任何顺序返回答案。
 * 如果不能，则返回列表 [-1]。
 *
 *  示例 1：
 *    1
 *   /
 *  2
 *  输入：root = [1,2], voyage = [2,1]
 *  输出：[-1]
 *
 *  示例 2：
 *    1
 *   / \
 *  2   3
 *  输入：root = [1,2,3], voyage = [1,3,2]
 *  输出：[1]
 */
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * 因为各个节点的值都不一样, 因此遍历过程中
 * 如果当前值与voyage值不匹配, 我们只能尝试翻转去匹配
 * 如果翻转过后还是不匹配, 那么就不能满足要求
 */
class Solution {
public:
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
        dfs(root, voyage);
        return ans;
    }

private:
    vector<int> ans;
    int idx = 0; //当前遍历voyage的idx
    void dfs(TreeNode* node, vector<int>& voyage) {
        if (node == nullptr) return;
        if (node->val != voyage[idx]) {
            //当前节点与voyage不匹配, 无法满足voyage的输出, 返回
            ans.clear();
            ans.push_back(-1);
            return;
        }
        TreeNode* next = nullptr;
        if (node->right) next = node->right;
        if (node->left) next = node->left;
        if (next != nullptr && next->val != voyage[idx+1]) {
            //下一个要遍历的节点与voyage下一个值不匹配时, 就翻转
            ans.push_back(node->val);
            swap(node->left, node->right);
        }
        idx++;
        dfs(node->left, voyage);
        dfs(node->right, voyage);
    }
};