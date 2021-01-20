/**
 * Leetcode 1377. T 秒后青蛙的位置
 * 给你一棵由 n 个顶点组成的无向树，顶点编号从 1 到 n。青蛙从 顶点 1 开始起跳。规则如下：
 *  (1)在一秒内，青蛙从它所在的当前顶点跳到另一个 未访问 过的顶点（如果它们直接相连）。
 *  (2)青蛙无法跳回已经访问过的顶点。
 *  (3)如果青蛙可以跳到多个不同顶点，那么它跳到其中任意一个顶点上的机率都相同。
 *  (4)如果青蛙不能跳到任何未访问过的顶点上，那么它每次跳跃都会停留在原地。
 * 无向树的边用数组 edges 描述，其中
 * edges[i] = [from, to] 意味着存在一条直接连通 from 和 to 两个顶点的边。
 * 返回青蛙在 t 秒后位于目标顶点 target 上的概率。
 *
 * 示例 1：
 *      1
 *    / \ \
 *   2   3 7
 *  / \   \
 * 4  6    5
 * 输入：n = 7, edges = [[1,2],[1,3],[1,7],[2,4],[2,6],[3,5]], t = 2, target = 4
 * 输出：0.16666666666666666
 * 解释：青蛙的跳跃路径为: 青蛙从顶点 1 起跳，
 *      第 1 秒 有 1/3 的概率跳到顶点 2 ，
 *      然后第 2 秒 有 1/2 的概率跳到顶点 4，
 *      因此青蛙在 2 秒后位于顶点 4 的概率是 1/3 * 1/2 = 1/6 = 0.16666666666666666 。
 */
#include <vector>
using std::vector;

class Solution {
public:
    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
        graph.resize(n + 1, vector<int>());
        /* 无向图即双向边 */
        for (auto& e : edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }
        dfs(1, 0, target, t, 1);
        return ans;
    }

private:
    double ans = 0;
    vector<vector<int>> graph;
    /**
     * dfs判断
     * @param node 当前节点
     * @param parent 当前节点的父节点
     * @param target target节点
     * @param t 当前剩余时间
     * @param pr 跳到当前节点的概率
     */
    void dfs(int node, int parent, int target, int t, double pr) {
        if (t == 0) {
            /* 耗时完毕 */
            if (node == target)
                /* 如果跳到了target节点, 返回pr */
                ans = pr;
            return;
        }
        vector<int>& v = graph[node];
        int cnt = v.size();
        if (v.empty() || (cnt == 1 && v[0] == parent)) {
            /* 如果当前节点没有孩子节点 */
            if (node == target)
                /* 如果跳到了target节点, 之后的时间会停留在原地, 返回pr */
                ans = pr;
            return;
        }
        /* 概率除以所有孩子节点的个数 */
        if (parent != 0) cnt--;
        pr /= cnt;
        t--;
        for (int n : v) {
            if (n == parent) continue;
            dfs(n, node, target, t, pr);
        }
    }
};