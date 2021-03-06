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
 * 思路: dfs
 * 利用level变量从结果集中获取对应层的遍历结果链表
 * 利用链表, 加到尾部加到头部, 来分别代表顺序和倒序
 * 
 * 另外一种bfs的解法看另外一个同名文件
 */
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        dfs(root, 0);
        int size = v.size();
        vector<vector<int>> ans(size);
        for (int i = 0; i < size; i++) {
            ans[i] = vector<int>(v[i].begin(), v[i].end());
        }
        return ans;
    }

private:
    vector<deque<int>> v;
    void dfs(TreeNode *root, int level) {
        if (root == nullptr) return;
        if (v.size() <= level)
            v.push_back(deque<int>());
        auto& q = v[level]; //注意要用reference, 不然产生copy了
        //等价于level % 2 == 0
        if (!(level & 1))
            //偶数层加到队列尾, 先进先出, 顺序输出
            q.push_back(root->val); 
        else
            //奇数层加到队列头, 先进后出, 逆序输出
            q.push_front(root->val); 
        level++;
        dfs(root->left, level);
        dfs(root->right, level);
    }
};