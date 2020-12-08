/**
 * 剑指 Offer 32 - III. 从上到下打印二叉树 III
 * 请实现一个函数按照之字形顺序打印二叉树，即第一行按照从左到右的顺序打印，
 * 第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，其他行以此类推。
 * 例如:
 * 给定二叉树: [3,9,20,null,null,15,7],
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * 返回其层次遍历结果：
 *  [
 *    [3],
 *    [20,9],
 *    [15,7]
 *  ]
 */
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/* 利用奇偶层判断打印逻辑, root为第0层 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        deque<TreeNode*> q;
        if (root == NULL) return ans;
        /* true代表当成从左往右打印 */
        bool flag = true;
        q.push_front(root);
        while (!q.empty()) {
            int size = q.size();
            vector<int> level(size, 0);
            for (int i = 0; i < size; i++) {
                TreeNode* node = NULL;
                if (flag) {
                    node = q.front();
                    q.pop_front();
                } else {
                    node = q.back();
                    q.pop_back();
                }
                level[i] = node->val;
                if (flag) {
                    /* 下一层为从右往左打印, 会从队列尾部获取节点
                     * 因此应该让右孩子处于队列尾部
                     * 故先push_back左孩子
                     */
                    if (node->left) q.push_back(node->left);
                    if (node->right) q.push_back(node->right);
                } else {
                    /* 下一层为从左往右打印, 会从队列头部获取节点
                     * 因此应该让左孩子处于队列头部
                     * 故先push_front右孩子 
                     */
                    if (node->right) q.push_front(node->right);
                    if (node->left) q.push_front(node->left);
                }
            }
            ans.push_back(level);
            flag = !flag;
        }
        return ans;
    }
};