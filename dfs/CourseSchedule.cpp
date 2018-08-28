#include <iostream>
#include <vector>
using namespace std;

/**
 * leetcode 207. Course Schedule
 * 有一系列课程, 有些课程需要在学习了某一门课程后才能学习
 * 给定一系列这样的关系, 问是否可以完成所有课程
 * 例如:
 * Input: 2, [[0,1]]
 * Output: true
 * Explanation: There are a total of 2 courses to take.
 *           To take course 1 you should have finished course 0. So it is possible.
 *
 * Input: 2, [[1,0],[0,1]]
 * Output: false
 * Explanation: There are a total of 2 courses to take.
 *           To take course 1 you should have finished course 0, and to take course 0 you should
 *           also have finished course 1. So it is impossible.
 *
 * 实质上就是判断图是否存在环路, 可利用拓扑排序
 * Kahn算法 和 DFS算法
 */

/**
 * 基于dfs的拓扑排序
 * 从起点出发, 维护一个标记数组, 表示哪些点是访问过的, 每次出发都初始化为false
 * 一直走下去, 若走到一个已经走过的点, 表示有环; 若直到走到出度为0的顶点都没问题, 代表从原始顶点出发的所有路径都没有环
 */

/* 我最初的做法(超时)
 * 原因:重复递归过多
 * 例如:
 * 1->2->3->4
 * 我们在处理顶点1的的时候, 得知从1出发的所有路径都是没有环路的
 * 这就代表了2, 3, 4也是这样, 理应不需要重复处理
 * 但是我这个做法重复递归了, 所以超时了
 */
class TimeLimitExceeded {
public:
    bool topological_sort(int vertex_num, vector<pair<int, int>>& graph) {
        vector<bool> visit(vertex_num, false);
        for (int i = 0; i < vertex_num; ++i) {
            if (dfs(i, graph, visit))
                return false;
        }
        return true;
    }

    /**
     * 从某个顶点出发, 判断它的所有路径是否有环
     * @param vertex 出发的顶点
     * @param graph 图
     * @param visit 某一条路径的标记数组
     * @return 有环返回true, 无环返回false
     */
    bool dfs(int vertex, vector<pair<int, int>>& graph, vector<bool>& visit) {
        if (visit[vertex]) return true;
        visit[vertex] = true;
        for (auto p : graph) {
            if (p.first == vertex) {
                if (dfs(p.second, graph, visit))
                    return true;
            }
        }
        return visit[vertex] = false;
    }
};

/*
 * 改良做法
 * 我们多维护一个集合, 用来表示哪些顶点在之前的顶点的处理过程中, 已经被判明是没有环的了
 */
class Solution {
    bool topological_sort(int vertex_num, vector<pair<int, int>>& graph) {
        vector<bool> visit(vertex_num, false);  //新的标记数组
        vector<bool> onPath(vertex_num, false); //每条路径的标记数组
        for (int i = 0; i < vertex_num; ++i) {
            if (!visit[i] && dfs(i, graph, visit, onPath))
                return false;
        }
        return true;
    }

    bool dfs(int vertex, vector<pair<int, int>>& graph, vector<bool>& visit, vector<bool>& onPath) {
        if (visit[vertex]) return false;    //之前判断过无环, 直接返回
        onPath[vertex] = visit[vertex] = true;
        for (auto p : graph) {
            if (p.first == vertex) {
                if (onPath[p.second] || dfs(p.second, graph, visit, onPath))
                    return true;
            }
        }
        return onPath[vertex] = false;
    }
};