#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

/* leetcode 310. Minimum Height Trees
 * 给定一个图, 符合树的结构, 任何一个顶点都可以作为树的根节点
 * 求所有树中, 树高最小的所有根节点
 *
 * 思路:
 * 首先, 从简单的入手
 * 假设这幅图就是一条线走到底, 那么树高最小的肯定是中间的个顶点或者是中间的两个顶点(取决于是奇数还是偶数)
 * 那么我们可以用两个指针从两头开始遍历, 当我们这两个指针相等或者只相差一, 那么我们就找到了中间节点
 *
 * 现在我们来看这个符合树的特性的图, 我们可以从所有的叶子节点(度为1的顶点)出发, 当两个指针相遇时, 我们留下一个指针, 直到最后两个指针相遇
 * 过程跟拓扑排序很相似, 找到叶子节点, 删除跟它相关的边; 删除边之后, 有些顶点会变成叶子节点, 一直循环到叶子节点只剩一个或者两个
 * 剩下的叶子节点就是我们的结果
 */

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
        if (n == 1) return vector<int>({1});
        vector<unordered_set<int>> adj(n, unordered_set<int>());
        for (auto p : edges) {
            adj[p.first].insert(p.second);
            adj[p.second].insert(p.first);
        }
        vector<int> leaves;
        for (int i = 0; i < n; i++)
            if (adj[i].size() == 1)
                leaves.push_back(i);
        while (n > 2) {
            n -= leaves.size();
            vector<int> new_leaves;
            for (int i : leaves) {
                auto iter = adj[i].begin();
                int j = *iter;
                adj[j].erase(i);
                if (adj[j].size() == 1)
                    new_leaves.push_back(j);
            }
            leaves.clear();
            leaves.swap(new_leaves);
        }
        return leaves;
    }
};
