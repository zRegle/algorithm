/**
 * leetcode 103. Binary Tree Zigzag Level Order Traversal
 * 给定一棵二叉树, 要求Z字层次遍历, 返回一个数组, 每个元素是某一层的遍历结果
 *
 * 例如:
 *   3
 *  / \
 * 9  20
 *   / \
 *  15  7
 *
 * 返回:
 * [
 *  [3],
 *  [20,9],
 *  [15,7]
 * ]
 *
 * 思路: bfs
 * 利用队列, 在每次循环的时候, 获取队列大小, 即当前层的节点数
 * 然后维持一个布尔变量表示是否倒序, 利用size-i-1填充当前遍历结果数组
 *
 * 另外一种dfs的解法请去看dfs文件夹
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
public:
    vector<vector<int>> res;

    //bfs
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if (root != nullptr) {
            queue<TreeNode*> q;
            bool reverse = false;
            q.push(root);
            while (!q.empty()) {
                int level_num = q.size();
                vector<int> level(level_num);
                for (int i = 0; i < level_num; ++i) {
                    TreeNode* cur = q.front();
                    q.pop();
                    int idx = reverse ? level_num-i-1 : i;
                    level[idx] = cur->val;
                    if (cur->left) q.push(cur->left);
                    if (cur->right) q.push(cur->right);
                }
                reverse = !reverse;
                res.push_back(level);
            }
        }
        return res;
    }
};