#include <stack>
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
 */

/*
 * 拓扑排序
 * 两个数组结构: 一个栈(队列)用来保存入度为0的顶点, 一个数组用来统计顶点的入度
 * 过程:
 * 1.初始化: 将入度为0的顶点入栈(队列)
 * 2.循环中: 弹出栈顶元素, 输出该顶点, 将与该顶点指向的邻居的入度数减一
 *           将入度为0的顶点入栈(队列)
 * 当栈为空时, 判断是否还有节点未输出, 如果是, 说明在循环中找不到入度为0的顶点, 说明有环
 */
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> indegree(numCourses, 0);
        vector<vector<int>> graph(numCourses, vector<int>());
        /* 构建邻接矩阵并且统计入度 */
        for (vector<int>& edge : prerequisites) {
            graph[edge[0]].push_back(edge[1]);
            indegree[edge[1]]++;
        }
        /* 入度为0的入栈 */
        stack<int> s;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0)
                s.push(i);
        }
        /* 拓扑排序 */
        int node;
        while (!s.empty()) {
            node = s.top(); s.pop();
            numCourses--; /* 输出该节点 */
            for (int neighbor : graph[node])
                if (--indegree[neighbor] == 0)
                    s.push(neighbor);
        }
        /* 还有节点未输出, 有环 */
        return numCourses == 0;
    }
};