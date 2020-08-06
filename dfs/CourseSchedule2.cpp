/* Leetcode 210.课程表 II
 * 现在你总共有 n 门课需要选，记为 0 到 n-1。
 * 在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们: [0,1]
 * 给定课程总量以及它们的先决条件，返回你为了学完所有课程所安排的学习顺序。
 * 可能会有多个正确的顺序，你只要返回一种就可以了。如果不可能完成所有课程，返回一个空数组。
 */
#include <vector>
#include <algorithm>
using namespace std;

/* leetcode 207的变体, 输出拓扑排序的序列即可 */
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> ans;
        vector<vector<int>> graph(numCourses, vector<int>());
        for (vector<int> &edge : prerequisites) {
            graph[edge[1]].push_back(edge[0]);
        }
        vector<int> status(numCourses, 0);
        /* 检查每个节点是否有环路, 并同时拓扑排序
         * 不用担心出现重复的排序结果, status[node] = 2控制住递归
         */
        for (int i = 0; i < numCourses; i++)
            if (!dfs(i, status, graph, ans))
                return vector<int>();
        reverse(ans.begin(), ans.end());
        return ans;
    }

private:
    bool dfs(int node, vector<int>& status, vector<vector<int>>& graph, vector<int>& ans) {
        if (status[node] == 1) return false;
        if (status[node] == 2) return true;
        status[node] = 1;
        for (int neighbor : graph[node])
            if (!dfs(neighbor, status, graph, ans))
                return false;
        status[node] = 2;
        /* 它的所有邻居都搜索完了, 回溯到这个节点
         * 那么从这个节点开始满足拓扑排序的要求, 并且对应的序列已经反转好放到ans里了
         */
        ans.push_back(node);
        return true;
    }
};