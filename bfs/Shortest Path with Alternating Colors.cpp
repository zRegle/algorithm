/**
 * Leetcode 1129. 颜色交替的最短路径
 * 在一个有向图中，节点分别标记为 0, 1, ..., n-1。这个图中的每条边不是红色就是蓝色，且存在自环或平行边。
 * red_edges 中的每一个 [i, j] 对表示从节点 i 到节点 j 的红色有向边。
 * 类似地，blue_edges 中的每一个 [i, j] 对表示从节点 i 到节点 j 的蓝色有向边。
 * 返回长度为 n 的数组 answer，其中 answer[X] 是从节点 0 到节点 X 的红色边和蓝色边交替出现的最短路径的长度。
 * 如果不存在这样的路径，那么 answer[x] = -1。
 */
#include <vector>
#include <queue>
using namespace std;

/**
 * 0-1 BFS, 搜索的状态为: <当前节点, 从哪种颜色的边到达当前节点>
 * 例如, 从红色边到达节点27
 * 那么state = <27, 0>, 反之为<27, 1>
 */
#define MAKE_STATE(x, flag) x << 1 | flag //压缩状态, 用最低位的bit记录颜色, 0代表红色, 1代表蓝色
#define GET_FLAG(x) x & 1
#define GET_NODE(x) x >> 1

class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& red_edges, vector<vector<int>>& blue_edges) {
        //构建红蓝边的邻接矩阵
        vector<vector<int>> red(n, vector<int>());
        for (auto& e : red_edges) {
            red[e[0]].push_back(e[1]);
        }
        vector<vector<int>> blue(n, vector<int>());
        for (auto& e : blue_edges) {
            blue[e[0]].push_back(e[1]);
        }
        vector<int> ans(n, -1);
        /**
         * 一共有n个顶点, 每个顶点有两种状态:
         * 从红边到达该顶点和从蓝边到达该顶点
         * 因此一共有n * 2个元素
         */
        vector<int> vis(n << 1, 0);
        queue<int> q;
        int state = MAKE_STATE(0, 1);
        /**
         * 从节点0出发, 可以选择红色边或者蓝色边到下一个节点
         * 那么可以认为就是分别有两个dummy node通过红色边和蓝色边到达节点0
         */
        q.push(state); vis[state] = 1;
        state = MAKE_STATE(0, 0);
        q.push(state); vis[state] = 1;
        int cnt = 0;
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                int state = q.front(); q.pop();
                int node = GET_NODE(state), flag = GET_FLAG(state);
                if (ans[node] == -1) 
                    //第一次到达该节点, 此时就是最短路径
                    ans[node] = cnt;
                if (flag == 0) {
                    //通过红色边到达当前节点的, 只能选择蓝色边到下一个节点
                    for (int neighbor : blue[node]) {
                        state = MAKE_STATE(neighbor, 1);
                        if (vis[state] == 0) {
                            vis[state] = 1;
                            q.push(state);
                        }
                    }
                } else {
                    //通过蓝色边到达当前节点的, 只能选择红色边到下一个节点
                    for (int neighbor : red[node]) {
                        state = MAKE_STATE(neighbor, 0);
                        if (vis[state] == 0) {
                            vis[state] = 1;
                            q.push(state);
                        }
                    }
                }
            }
            cnt++;
        }
        return ans;
    }
};