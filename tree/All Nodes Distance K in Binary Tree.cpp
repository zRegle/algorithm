/* Leetcode 863.二叉树中所有距离为 K 的结点
 * 给定一个二叉树（具有根结点 root）， 一个目标结点 target ，和一个整数值 K 。
 * 返回到目标结点 target 距离为 K 的所有结点的值的列表。 答案可以以任何顺序返回。
 * 示例:
 *  target = 5, K = 2
 *     3
 *    /  \
 *   5   +1
 *  / \  / \
 * 6  2 0   8
 *   / \
 *  +7  +4
 * 返回[1, 7, 4]
 */
#include <cstddef>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/* 核心思想: 建立节点到父节点的引用, 就可以从target开始DFS或者BFS了 */

class DFS {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        dfs(root, NULL);
        set.insert(target);
        /* 以target为根节点进行DFS */
        findK(target, 0, K);
        return ans;
    }

private:
    vector<int> ans;
    /* 节点到父节点的映射 */
    unordered_map<TreeNode*, TreeNode*> map;
    /* DFS中, 存在两个节点对应同一个父节点, 如果不记录已经访问过的节点
     * 那么这两个节点都会dfs他的parent, 造成递归爆炸
     */
    unordered_set<TreeNode*> set;

    void dfs(TreeNode* node, TreeNode* parent) {
        if (node != NULL) {
            map[node] = parent;
            dfs(node->left, node);
            dfs(node->right, node);
        }
    }

    void findK(TreeNode* node, int depth, int K) {
        if (node != NULL) {
            if (depth == K) {
                /* 达到深度K, 没必要继续DFS, 直接返回 */
                ans.push_back(node->val);
                return;
            }
            depth++;
            if (set.find(map[node]) == set.end()) {
                set.insert(map[node]);
                findK(map[node], depth, K);
            }
            if (set.find(node->left) == set.end()) {
                set.insert(node->left);
                findK(node->left, depth, K);
            }
            if (set.find(node->right) == set.end()) {
                set.insert(node->right);
                findK(node->right, depth, K);
            }
        }
    }
};

class BFS {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        vector<int> ans;
        /* 建立节点到父节点的映射关系 */
        unordered_map<TreeNode*, TreeNode*> map;
        queue<TreeNode*> q;
        q.push(root); map[root] = NULL;
        while (!q.empty()) {
            auto node = q.front(); q.pop();
            if (node->left) {
                map[node->left] = node;
                q.push(node->left);
            }
            if (node->right) {
                map[node->right] = node;
                q.push(node->right);
            }
        }
        /* 以target为根节点, 进行BFS */
        unordered_set<TreeNode*> set;
        q.push(target); set.insert(target);
        int dist = 0;
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                auto node = q.front(); q.pop();
                if (dist == K) {
                    /* 到达深度K, 没必要继续BFS了, 返回这层的所有节点 */
                    ans.push_back(node->val);
                    continue;
                }
                auto parent = map[node];
                if (parent != NULL && set.find(parent) == set.end()) {
                    q.push(parent);
                    set.insert(parent);
                }
                if (node->left != NULL && set.find(node->left) == set.end()) {
                    q.push(node->left);
                    set.insert(node->left);
                }
                if (node->right != NULL && set.find(node->right) == set.end()) {
                    q.push(node->right);
                    set.insert(node->right);
                }
            }
            dist++;
        }
        return ans;
    }
};