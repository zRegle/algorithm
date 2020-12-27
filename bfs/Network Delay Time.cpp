/**
 * Leetcode 743. 网络延迟时间
 * 有 N 个网络节点，标记为 1 到 N。
 * 给定一个列表 times，表示信号经过有向边的传递时间。 times[i] = (u, v, w)，
 * 其中 u 是源节点，v 是目标节点， w 是一个信号从源节点传递到目标节点的时间。
 * 现在，我们从某个节点 K 发出一个信号。需要多久才能使所有节点都收到信号？
 * 如果不能使所有节点收到信号，返回 -1。
 */
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

/**
 * 利用dijkstra求出从K到所有顶点的最短距离, 返回其最大值
 * 可以想成从结点K开始有水流向周围扩散, 当水流到达最远的一个结点时,
 * 那么水一定流过其他所有的结点了
 */
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        unordered_map<int, vector<pair<int, int>>> map;
        //构建邻接矩阵, pair.firset = 邻居, pair.second = 距离
        for (auto& edge : times) {
            if (map.find(edge[0]) == map.end())
                map[edge[0]] = vector<pair<int, int>>();
            map[edge[0]].push_back({edge[1], edge[2]});
        }
        //初始化到各个邻居的distance数组
        vector<int> dist(N + 1, INT_MAX);
        for (auto& p : map[K]) {
            dist[p.first] = p.second;
        }
        dist[K] = dist[0] = 0;
        auto cmp = [&dist](int n1, int n2) -> bool {
            return dist[n1] > dist[n2];
        };
        //构建最小堆, 保存当前距离K最近的顶点
        priority_queue<int, vector<int>, decltype(cmp)> q(cmp);
        q.push(K);
        vector<int> vis(N + 1, 0);
        while (!q.empty()) {
            int node = q.top(); q.pop();
            if (vis[node] == 1) continue; //for循环里可能push了多个neighbor, 冗余
            vis[node] = 1;
            for (auto& p : map[node]) {
                int neighbor = p.first;
                if (vis[neighbor] == 1) continue;
                dist[neighbor] = min(dist[neighbor], dist[node] + p.second);
                q.push(neighbor);
                //push之后不能设置neighbor为visited, 因为这个for循环里还可能会更新dist[neighbor]
            }
        }
        //返回所有邻居中距离最远的
        int ans = -1;
        for (int i = 1; i <= N; i++) {
            if (dist[i] == INT_MAX) return -1;
            ans = max(ans, dist[i]);
        }
        return ans;
    }
};