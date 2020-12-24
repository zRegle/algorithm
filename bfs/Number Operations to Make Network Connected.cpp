/** 
 * Leetcode 1319. 连通网络的操作次数
 * 用以太网线缆将 n 台计算机连接成一个网络，计算机的编号从 0 到 n-1。线缆用 connections 表示，
 *  其中 connections[i] = [a, b] 连接了计算机 a 和 b。
 * 网络中的任何一台计算机都可以通过网络直接或者间接访问同一个网络中其他任意一台计算机。
 * 给你这个计算机网络的初始布线 connections，你可以拔开任意两台直连计算机之间的线缆，
 *  并用它连接一对未直连的计算机。请你计算并返回使所有计算机都连通所需的最少操作次数。如果不可能，则返回 -1 。 
 */
#include <vector>
#include <queue>
#include <list>
using namespace std;

/* 本质上就是求无向图中连通分量的个数 */
class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        int cable = connections.size();
        /* n台机子至少需要n-1条线缆连接 */
        if (cable < n - 1) return -1;
        /* 统计各个顶点的邻居 */
        vector<list<int>> graph(n, list<int>());
        for (vector<int>& edge : connections) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        int component = 0; /* 连通分量个数 */
        vector<int> visited(n, 0);
        for (int i = 0; i < n; i++) {
            if (visited[i] == 0) {
                bfs(i, graph, visited);
                component++;
            }
        }
        return component - 1;
    }
private:
    /* bfs遍历从node出发, 能够达到的顶点, 此为一个连通分量 */
    void bfs(int node, vector<list<int>>& graph, vector<int>& visited) {
        queue<int> q;
        q.push(node);
        while (!q.empty()) {
            node = q.front(); q.pop();
            for (int neighbor : graph[node]) {
                if (visited[neighbor] == 0) {
                    q.push(neighbor);
                    visited[neighbor] = 1;
                }
            }
        }
    }
};