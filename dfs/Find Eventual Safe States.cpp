/**
 * Leetcode 802. 找到最终的安全状态
 * 在有向图中，以某个节点为起始节点，从该点出发，每一步沿着图中的一条有向边行走。
 * 如果到达的节点是终点（即它没有连出的有向边），则停止。
 * 对于一个起始节点，如果从该节点出发，无论每一步选择沿哪条有向边行走，
 * 最后必然在有限步内到达终点，则将该起始节点称作是 安全 的。
 *
 * 返回一个由图中所有安全的起始节点组成的数组作为答案。答案数组中的元素应当按 升序 排列。
 * 该有向图有 n 个节点，按 0 到 n - 1 编号，其中 n 是 graph 的节点数。
 * 图以下述形式给出：graph[i] 是编号 j 节点的一个列表，满足 (i, j) 是图的一条有向边。
 *
 * 示例 1：
 *  输入：graph = [[1,2],[2,3],[5],[0],[5],[],[]]
 *  输出：[2,4,5,6]
 * 示例 2：
 *  输入：graph = [[1,2,3,4],[1,2],[3,4],[0,4],[]]
 *  输出：[4]
 *
 * 提示：
 *  (1)n == graph.length
 *  (2)1 <= n <= 10^4
 *  (3)0 <= graph[i].length <= n
 *  (4)graph[i] 按严格递增顺序排列。
 *  (5)图中可能包含自环。
 *  (6)图中边的数目在范围 [1, 4 * 10^4] 内。
 */
#include <vector>
using namespace std;

/* 拓扑排序见bfs文件夹 */

#define UNSAFE 0
#define SAFE 1
#define IN_PATH 2
#define NOT_VISIT 3
class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> mark(n, NOT_VISIT);
        for (int x = 0; x < n; x++) {
            if (graph[x].empty())
                /* 出度为0的节点必然是safe */
                mark[x] = SAFE;
        }
        vector<int> ans;
        for (int x = 0; x < n; x++) {
            if (dfs(x, graph, mark))
                ans.push_back(x);
        }
        return ans;
    }

private:
    /**
     * dfs判断节点x是否安全
     * @param x 当前出发节点
     * @param graph self-explained
     * @param mark 标记数组
     * @return true -> safe, false -> unsafe
     */
    bool dfs(int x, vector<vector<int>>& graph, vector<int>& mark) {
        if (mark[x] == SAFE) return true;
        if (mark[x] == UNSAFE) return false;
        mark[x] = IN_PATH;
        bool flag = SAFE;
        for (int y : graph[x]) {
            if (mark[y] == IN_PATH) {
                flag = UNSAFE;
                break;
            }
            flag = dfs(y, graph, mark);
            if (!flag) break;
        }
        mark[x] = flag;
        return mark[x];
    }
};