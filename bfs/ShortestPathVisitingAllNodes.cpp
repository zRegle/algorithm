/**
 * Leetcode 847. 访问所有节点的最短路径
 * 给出 graph 为有 N 个节点（编号为 0, 1, 2, ..., N-1）的无向连通图。 
 * graph.length = N，且只有节点 i 和 j 连通时，j != i 在列表 graph[i] 中恰好出现一次。
 * 返回能够访问所有节点的最短路径的长度。你可以在任一节点开始和停止，也可以多次重访节点，并且可以重用边。
 *  
 * 示例 1：
 *  输入：[[1,2,3],[0],[0],[0]]
 *  输出：4
 *  解释：一个可能的路径为 [1,0,2,0,3]
 * 示例 2：
 *  输入：[[1],[0,2,4],[1,3,4],[2],[1,2]]
 *  输出：4
 *  解释：一个可能的路径为 [0,1,4,2,3]
 *  
 * 提示：
 * 1 <= graph.length <= 12
 * 0 <= graph[i].length < graph.length
 */ 
#include <vector>
#include <queue>
using namespace std;

/* 多起点BFS泛洪 */
class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        /* 第一个元素: 顶点对应的位图, 1->已经访问, 0->还没被访问
         *            因为 1 <= N <= 12, 我们使用位图来压缩当前路径中已经访问过的顶点, 不然会TLE
         * 第二个元素: 当前路径到达的节点
         */
        queue<pair<int, int>> q;
        /* visited[i][j]表示: 走到j顶点从而达到状态i时, 是否已经遍历过
         * 譬如visited[5][1] = false(5的二进制表示为101)
         * 表示走到顶点2时, 已经走过了顶点0和2, 这个状态之前还没遍历过
         */
        vector<vector<int>> visited(1 << n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            /* 多起点bfs, 因为我们可以从任意一个顶点出发 */
            visited[1 << i][i] = 1;
            q.push({1 << i, i});
        }
        int level = 0;
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                auto p = q.front(); q.pop();
                int state = p.first, node = p.second;
                /* 所有节点都访问完毕, 直接返回 */
                if (state == (1 << n) - 1) return level;
                for (int neighbor : graph[node]) {
                    /* 走到negihbor后, 已经访问过的顶点 */
                    int next = state | (1 << neighbor);
                    /* 这个状态之前还没遍历过 */
                    if (visited[next][neighbor] == 0) {
                        visited[next][neighbor] = 1;
                        q.push({next, neighbor});
                    }
                }
            }
            level++;
        }
        return 0;
    }
};