#include <iostream>
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
 * Kahn算法 和 DFS算法
 */

/*
 * Kahn算法
 * 两个数组结构: 一个栈用来保存入度为0的顶点, 一个数组用来统计顶点的入度
 * 过程:
 * 1.初始化: 将入度为0的顶点入栈
 * 2.循环中: 弹出栈顶元素, 输出该顶点, 将与该顶点指向的邻居的入度数减一
 *           将入度为0的顶点入栈
 * 当栈为空时, 判断计数变量是否等于顶点数, 若不相等, 说明在循环中找不到入度为0的顶点, 说明有环
 */
class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        stack<int> s;
        vector<int> in(numCourses, 0);
        for (pair<int, int> p : prerequisites) {
            in[p.second]++;
        }
        for (int i = 0; i < numCourses; i++) {
            if (!in[i])
                s.push(i);
        }
        int cnt = 0;
        while (!s.empty()) {
            int cur = s.top(); s.pop(); cnt++;
            for (auto p : prerequisites) {
                if (cur == p.first) {
                    in[p.second]--;
                    if (!in[p.second])
                        s.push(p.second);
                }
            }
        }
        return cnt == numCourses;
    }
};