/**
 * Leetcode 399. 除法求值
 * 给你一个变量对数组 equations 和一个实数值数组 values 作为已知条件，
 * 其中 equations[i] = [Ai, Bi] 和 values[i] 共同表示等式 Ai / Bi = values[i] 。
 * 每个 Ai 或 Bi 是一个表示单个变量的字符串。
 *
 * 另有一些以数组 queries 表示的问题，其中 queries[j] = [Cj, Dj] 表示第 j 个问题，
 * 请你根据已知条件找出 Cj / Dj = ? 的结果作为答案。
 *
 * 返回 所有问题的答案 。如果存在某个无法确定的答案，则用 -1.0 替代这个答案。
 * 如果问题中出现了给定的已知条件中没有出现的字符串，也需要用 -1.0 替代这个答案。
 *
 * 注意：输入总是有效的。你可以假设除法运算中不会出现除数为 0 的情况，且不存在任何矛盾的结果。
 *
 * 示例 1：
 * 输入：equations = [["a","b"],["b","c"]], values = [2.0,3.0],
 *      queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
 * 输出：[6.00000,0.50000,-1.00000,1.00000,-1.00000]
 * 解释：
 *  条件：a / b = 2.0, b / c = 3.0
 *  问题：a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
 *  结果：[6.0, 0.5, -1.0, 1.0, -1.0 ]
 *
 * 示例 2：
 *  输入：equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0],
 *       queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
 *  输出：[3.75000,0.40000,5.00000,0.20000]
 *  注意："bc"和"cd"是单独两个变量, 不是"b * c", "c * d"
 */
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

/* 总体思路:
 * 例如a / b = 4
 * 可以看做一条a -> b,权重为4的边
 * 和一条b -> a, 权重为1/4的边 
 * 求x / y就是找是否有一条从x到y的路径, 然后返回权重之积 */

 /**
  * 带权重并查集方法请参考连接
  * https://leetcode-cn.com/problems/evaluate-division/solution/399-chu-fa-qiu-zhi-nan-du-zhong-deng-286-w45d/
  */

class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        /**
         * 构建图:
         * key -> 节点
         * value -> pair<string, double>数组, 每一对pair<x, y>的含义如下:
         *          存在一条key -> x的边, 权重为y
         */
        for (int i = 0; i < equations.size(); i++) {
            string& first = equations[i][0], second = equations[i][1];
            if (graph.find(first) == graph.end())
                graph[first] = vector<pair<string, double>>();
            graph[first].push_back({second, values[i]});
            if (graph.find(second) == graph.end())
                graph[second] = vector<pair<string, double>>();
            graph[second].push_back({first, 1 / values[i]});
        }
        vector<double> ans(queries.size());
        unordered_set<string> vis;
        for (int i = 0; i < queries.size(); i++) {
            string from = queries[i][0], to = queries[i][1];
            /* 起点或者终点不在图内, 直接返回-1 */
            if (graph.find(from) == graph.end() || graph.find(to) == graph.end()) {
                ans[i] = -1;
                continue;
            }
            vis.insert(from);
            double v = dfs(from, to, vis);
            ans[i] = v;
            vis.clear();
        }
        return ans;
    }

private:
    unordered_map<string, vector<pair<string, double>>> graph;
    /**
     * dfs判断是否存在从cur到target的路径
     * @param cur 当前出发节点
     * @param target 目标节点
     * @param vis visited数组, 避免重复访问
     * @return 如果路径存在, 则返回从cur到target的路径权重之积;
     *         如果不存在, 返回-1
     */
    double dfs(string& cur, string& target, unordered_set<string>& vis) {
        if (cur == target)
            return 1;
        for (auto& edge : graph[cur]) {
            string next = edge.first;
            if (vis.find(next) == vis.end()) {
                vis.insert(next);
                double path = dfs(next, target, vis);
                if (path != -1)
                    return path * edge.second;
            }
        }
        return -1;
    }
};