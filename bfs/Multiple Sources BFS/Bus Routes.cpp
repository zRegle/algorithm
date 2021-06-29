/**
 * Leetcode 815. 公交路线
 * 给你一个数组 routes ，表示一系列公交线路，
 * 其中每个 routes[i] 表示一条公交线路，第 i 辆公交车将会在上面循环行驶。
 * 例如，路线 routes[0] = [1, 5, 7] 表示第 0 辆公交车会一直按序列
 *  1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 1 -> ... 这样的车站路线行驶。
 * 现在从 source 车站出发（初始时不在公交车上），要前往 target 车站。 期间仅可乘坐公交车。
 * 求出 最少乘坐的公交车数量 。如果不可能到达终点车站，返回 -1 。
 *
 * 示例 1：
 *  输入：routes = [[1,2,7],[3,6,7]], source = 1, target = 6
 *  输出：2
 *  解释：最优策略是先乘坐第一辆公交车到达车站 7 , 然后换乘第二辆公交车到车站 6 。
 * 示例 2：
 *  输入：routes = [[7,12],[4,5,15],[6],[15,19],[9,12,13]], source = 15, target = 12
 *  输出：-1
 *
 * 提示：
 *  (1)1 <= routes.length <= 500.
 *  (2)1 <= routes[i].length <= 10^5
 *  (3)routes[i] 中的所有值 互不相同
 *  (4)sum(routes[i].length) <= 10^5
 *  (5)0 <= routes[i][j] < 10^6
 *  (6)0 <= source, target < 10^6
 */
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <list>
using namespace std;

/**
 * 由于求解的目标是最少乘坐的公交车数量，对于同一辆公交车，
 * 乘客可以在其路线中的任意车站间无代价地移动，于是我们可以把公交路线当作点。
 * 如果两条公交路线有相同车站，则可以在这两条路线间换乘公交车，
 * 那么这两条公交路线之间可视作有一条长度为1的边。
 *
 * 这样建出的图包含的点数即为公交路线的数量，记作n。
 * 完成了建图后，我们需要先明确新的图的起点和终点，然后使用广度优先搜索，
 * 计算出的起点和终点的最短路径，从而得到最少换乘次数。
 */

/**
 * 第一种方案:
 * 直接枚举左右两端点，检查两点对应的两公交路线是否有公共车站。
 * 利用哈希表，我们可以将单次比较的时间复杂度优化到均摊O(n)。
 *
 * 时间: 1340 ms
 * 内存: 143 mb
 */
class Solution0 {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if (source == target) return 0;
        int n = routes.size();
        /* 公交的邻接矩阵 */
        vector<list<int>> graph(n);
        /* key -> bus id
         * value -> 这趟公交经过的车站 */
        vector<unordered_set<int>> map;
        queue<int> q;
        vector<int> visit(n);
        for (int i = 0; i < n; i++) {
            map[i].insert(routes[i].begin(), routes[i].end());
            if (map[i].find(source) != map[i].end()) {
                /* 多源bfs */
                q.push(i);
                visit[i] = true;
            }
        }
        /* 判断公交间是否有共通车站, 有则建边 */
        for (int i = 0; i < n-1; i++) {
            for (int j = i+1; j < n; j++) {
                for (int station : routes[i]) {
                    if (map[j].find(station) != map[j].end()) {
                        graph[i].push_back(j);
                        graph[j].push_back(i);
                        break;
                    }
                }
            }
        }
        int level = 1;
        /* bfs */
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                int bus = q.front(); q.pop();
                if (map[bus].find(target) != map[bus].end())
                    return level;
                for (int nBUS : graph[bus]) {
                    if (visit[nBUS] == false) {
                        q.push(nBUS);
                        visit[nBUS] = true;
                    }
                }
            }
            level++;
        }
        return -1;
    }
};
/**
 * 第二种方案:
 * 我们遍历所有公交路线，记录每一个车站属于哪些公交路线。
 * 然后我们遍历每一个车站，如果有多条公交路线经过该点，则在这些公交路线之间连边。
 */
class Solution1 {
public:
    /**
     * 时间: 504 ms
     * 内存: 143 mb
     */
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if (source == target) return 0;
        int n = routes.size();
        /* 公交车的邻接矩阵 */
        vector<list<int>> graph(n);
        /* key -> 车站id
         * value -> 经过这个车站的bus id*/
        unordered_map<int, unordered_set<int>> map;
        queue<int> q;
        vector<int> visit(n);
        for (int i = 0; i < n; i++) {
            for (int station : routes[i]) {
                for (int bus : map[station]) {
                    graph[i].push_back(bus);
                    graph[bus].push_back(i);
                }
                map[station].insert(i);
            }
        }
        /* 多源bfs */
        for (int bus : map[source]) {
            q.push(bus);
            visit[bus] = true;
        }
        int level = 1;
        /* bfs */
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                int bus = q.front(); q.pop();
                if (map[target].find(bus) != map[target].end())
                    return level;
                for (int nBUS : graph[bus]) {
                    if (visit[nBUS] == false) {
                        q.push(nBUS);
                        visit[nBUS] = true;
                    }
                }
            }
            level++;
        }
        return -1;
    }
    /**
     * 优化版本
     * 时间: 232 ms
     * 内存: 50 mb
     */
     int optimize(vector<vector<int>>& routes, int source, int target) {
        if (source == target) return 0;
        int n = routes.size();
        /* 公交的邻接矩阵 */
        vector<vector<int>> edge(n, vector<int>(n));
        /* key -> 车站id
         * value -> 经过这个车站的bus id*/
        unordered_map<int, vector<int>> rec;
        for (int i = 0; i < n; i++) {
            for (int site : routes[i]) {
                for (int j : rec[site]) {
                    edge[i][j] = edge[j][i] = true;
                }
                rec[site].push_back(i);
            }
        }
        /* 从source出发, 到达i车站需要的距离 */
        vector<int> dis(n, -1);
        queue<int> que;
        for (int bus : rec[source]) {
            dis[bus] = 1;
            que.push(bus);
        }
        while (!que.empty()) {
            int x = que.front();
            que.pop();
            for (int y = 0; y < n; y++) {
                if (edge[x][y] && dis[y] == -1) {
                    dis[y] = dis[x] + 1;
                    que.push(y);
                }
            }
        }
        int ret = INT_MAX;
        for (int bus : rec[target]) {
            if (dis[bus] != -1) {
                ret = min(ret, dis[bus]);
            }
        }
        return ret == INT_MAX ? -1 : ret;
     }
};