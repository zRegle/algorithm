/** 
 * Leetcode 1319. 连通网络的操作次数
 * 用以太网线缆将 n 台计算机连接成一个网络，计算机的编号从 0 到 n-1。线缆用 connections 表示，
 *  其中 connections{i} = {a, b} 连接了计算机 a 和 b。
 * 网络中的任何一台计算机都可以通过网络直接或者间接访问同一个网络中其他任意一台计算机。
 * 给你这个计算机网络的初始布线 connections，你可以拔开任意两台直连计算机之间的线缆，
 *  并用它连接一对未直连的计算机。请你计算并返回使所有计算机都连通所需的最少操作次数。如果不可能，则返回 -1 。 
 */
#include <vector>
#include <algorithm>
using namespace std;

/* 本质上就是求无向图中连通分量的个数
 * 利用并查集即可
 * 并查集: https://zhuanlan.zhihu.com/p/93647900
 */
class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        int cable = connections.size();
        /* n台机子至少需要n-1条线缆连接 */
        if (cable < n - 1) return -1;
        /* 初始化 */
        father.resize(n);
        for (int i = 0; i < n; i++) 
            father[i] = i;
        rank.resize(n); 
        fill(rank.begin(), rank.end(), 1);
        /* 最初各个节点都是一个集合 */
        int component = n;
        /* 开始合并 */
        for (vector<int>& edge : connections) {
            int n1 = edge[0], n2 = edge[1];
            if (merge(n1, n2))
                /* 发生了合并, 连通分量减一 */
                component--;
        }

        return component - 1;
    }
private:
    vector<int> father;
    vector<int> rank;

    int find(int x) {
        if (x == father[x])
            return x;
        else {
            father[x] = find(father[x]);
            return father[x];
        }
    }

    bool merge(int i, int j) {
        int x = find(i), y = find(j);
        /* 两者的父节点一致, 是在同一个集合, 不需要合并 */
        if (x == y) return false;
        /* 两者的父节点不在同一个集合, 需要合并成新一个集合  */
        if (rank[x] <= rank[y]) {
            father[x] = y;
        } else {
            father[y] = x;
        }
        if (rank[x] == rank[y])
            rank[y]++;
        return true;
    }
};