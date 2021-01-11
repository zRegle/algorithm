/**
 * Leetcode 1519.子树中标签相同的节点数
 * 
 * 给你一棵树（即，一个连通的无环无向图），这棵树由编号从 0  到 n - 1 的 n 个节点组成，
 * 且恰好有 n - 1 条 edges 。树的根节点为节点 0 ，树上的每一个节点都有一个标签，
 * 也就是字符串 labels 中的一个小写字符（编号为 i 的 节点的标签就是 labels[i] ）
 * 
 * 边数组 edges 以 edges[i] = [ai, bi] 的形式给出，该格式表示节点 ai 和 bi 之间存在一条边。
 * 
 * 返回一个大小为 n 的数组，其中 ans[i] 表示第 i 个节点的子树中与节点 i 标签相同的节点数。
 * 
 * 树 T 中的子树是由 T 中的某个节点及其所有后代节点组成的树。
 * 
 * 例如: (数字为节点的编号, 数字下的字母为节点的标签)
 *        0
 *      / a \
 *     /     \
 *    1       2    
 *   /b\     /a\
 *  /   \   /   \
 * 4    5  3     6
 * d    c  e     d
 * 输入：n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], labels = "abaedcd"
 * 输出：[2,1,1,1,1,1,1]
 * 解释：节点 0 的标签为 'a' ，以 'a' 为根节点的子树中，节点 2 的标签也是 'a' ，因此答案为 2 。
 *       注意树中的每个节点都是这棵子树的一部分。节点 1 的标签为 'b' ，节点 1 的子树包含节点 1、4 和 5，
 *       但是节点 4、5 的标签与节点 1 不同，故而答案为 1（即，该节点本身）。
 */
#include <string>
#include <vector>
#include <list>
using namespace std;

/* 此题规定了0为根节点 */
class Solution {
public:
    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
        graph.resize(n, list<int>());
        /* 因为是个无向图, 因此不确定哪个是父节点, 先构建邻接矩阵 */
        for (auto e : edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }
        map.resize(n, vector<int>(26, 0));
        dfs(0, -1, labels);
        vector<int> ans(n, 0);
        for (int i = 0; i < n; i++) {
            ans[i] = map[i][labels[i] - 'a'];
        }
        return ans;
    }
private:
    /* 邻接矩阵 */
    vector<list<int>> graph;
    /* 每个节点的子树中, 各个英文字母的计数 */
    vector<vector<int>> map;
    /**
     * 统计cur节点的子树中, 各个英文字母出现的次数
     * \param cur 子树的根节点
     * \param parent cur的父节点, 避免子节点反dfs到父节点
     * \param labels 标签字符串
     */
    void dfs(int cur, int parent, const string& labels) {
        map[cur][labels[cur] - 'a']++;
        for (const auto& neighbor : graph[cur]) {
            if (neighbor == parent) continue;
            dfs(neighbor, cur, labels);
            for (int i = 0; i < 26; i++)
                map[cur][i] += map[neighbor][i];
        }
    }
};