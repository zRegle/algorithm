/**
 * Leetcode 547. 省份数量
 * 有 n 个城市，其中一些彼此相连，另一些没有相连。如果城市 a 与城市 b 直接相连，
 * 且城市 b 与城市 c 直接相连，那么城市 a 与城市 c 间接相连。
 * 省份 是一组直接或间接相连的城市，组内不含其他没有相连的城市。
 * 给你一个 n x n 的矩阵 isConnected ，其中 isConnected[i][j] = 1 表示第 i 个城市和第 j 个城市直接相连，
 * 而 isConnected[i][j] = 0 表示二者不直接相连。
 * 返回矩阵中 省份 的数量。
 */
#include <vector>
#include <stack>
using namespace std;

/* dfs求连通分量个数, 没啥好说的 */
class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<int> vis(n, 0);
        stack<int> stk;
        int component = 0;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                /* 这个节点还没遍历过, 表明不属于之前任何一个连通分量
                 * 因此连通分量个数加一
                 */
                component++;
                stk.push(i); vis[i] = 1;
                /* dfs遍历这个节点的连通分量 */
                while (!stk.empty()) {
                    int node = stk.top(); stk.pop();
                    for (int j = 0; j < n; j++) {
                        if (isConnected[node][j] && !vis[j]) {
                            vis[j] = 1;
                            stk.push(j);
                        }
                    }
                }
            }
        }
        return component;
    }
};