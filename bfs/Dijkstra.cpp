#include <vector>
#include <cstdint>
using std::vector;

/* dijkstra算法
 * source:  起点
 * target:  终点
 * n:   顶点个数
 * graph:   邻接矩阵
 */
int dijkstra(int source, int target, int n, vector<vector<int>>& graph) {
    /* 已经确定了从source到该顶点的最短路径的顶点 */
    vector<bool> visited(n, false);
    /* 从source出发到各顶点的当前最短距离, 也就是还未确定到这个顶点的最短路径 */
    vector<int> dist(n, INT32_MAX); 
    for (int i = 0; i < n; i++) {
        /* 初始化source各个邻接顶点的距离 */
        dist[i] = graph[source][i];
    }
    visited[source] = true;

    for (int i = 1; i < n; i++) {
        int min = INT32_MAX, k = -1;
        /* 从还未确定最短路径的顶点中挑选距离最短的一个 */
        for (int j = 0; j < n; j++) {
           if (visited[j] == false && dist[j] < min) {
               min = dist[j];
               k = j;
           }
        }
        /* 确定了从source到k的最短路径了 */
        visited[k] = true;
        for (int j = 0; j < n; j++) {
            /* 尝试更新还未确定最短路径的顶点的距离
             * visited[j] == false: 还未确定最短路径
             * graph[k][j] + dist[k] > dist[j]: 从source出发经过k到达j的距离比原来的路径要短
             */
            if (visited[j] == false && graph[k][j] + dist[k] > dist[j]) {
                dist[j] = graph[k][j] + dist[k];
            }
        }
    }

    return dist[target];
}