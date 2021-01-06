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
using std::vector;

/* 并查集求连通分量个数, 没啥好说的 */
class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        father.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++) {
            father[i] = i;
            rank[i] = 1;
        }
        int circle = n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (isConnected[i][j] && merge(i, j))
                    circle--;
            }
        }
        return circle;
    }
private:
    vector<int> father;
    vector<int> rank;

    int find(int x) {
        return x == father[x] ? x : (father[x] = find(father[x]));
    }

    bool merge(int i, int j) {
        int x = find(i), y = find(j);
        if (x == y) return false;
        if (rank[x] >= rank[y])
            father[y] = x;
        else
            father[x] = y;
        if (rank[x] == rank[y])
            rank[x]++;
        return true;
    }
};