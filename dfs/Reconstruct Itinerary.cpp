/**
 * Leetcode 332. 重新安排行程
 * 给定一个机票的字符串二维数组 [from, to]，子数组中的两个成员分别表示飞机出发和降落的机场地点，
 * 对该行程进行重新规划排序。所有这些机票都属于一个从 JFK（肯尼迪国际机场）出发的先生，
 * 所以该行程必须从 JFK 开始。
 *
 * 提示：
 *  (1)如果存在多种有效的行程，请你按字符自然排序返回最小的行程组合。
 *     例如，行程 ["JFK", "LGA"] 与 ["JFK", "LGB"] 相比就更小，排序更靠前
 *  (2)所有的机场都用三个大写字母表示（机场代码）。
 *  (3)假定所有机票至少存在一种合理的行程。
 *  (4)所有的机票必须都用一次 且 只能用一次。
 *
 * 示例：
 *  输入：[["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
 *  输出：["JFK","ATL","JFK","SFO","ATL","SFO"]
 *  解释：另一种有效的行程是["JFK","SFO","ATL","JFK","ATL","SFO"]。但是它自然排序更大更靠后。
 */
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

/* 求图的欧拉路径, Hierholzer算法:
 *  (1)从起点开始进行递归, 对于当前节点x，扫描与x相连的所有边，当扫描到一条(x,y)时，删除该边，并递归y。
 *  (2)扫描完所有边后，将x加入答案队列。
 *  (3)倒序输出答案队列。
 *
 * 为什么扫描完所有x边所有边后才加入答案队列?
 * 举个例子:
 *     NRT <-- JFK --> KUL
 *      |      ^
 *      |______|
 *  我们从JFK出发, 选择了KUL作为下一个递归起点, 我们就进入了「死胡同」, 无法输出结果了.
 *  概括起来就是, 我们从当前节点出发, 很那判断哪个分支是「死胡同」, 哪个不是
 *  
 *  不妨倒过来思考。我们注意到只有那个入度与出度差为 1 的节点会导致死胡同。而该节点必然是输出结果最后的节点。
 *  我们可以改变入栈的规则，当我们遍历完一个节点所连的所有节点后，我们才将该节点入栈（即逆序入栈）。
 *  
 *  对于当前节点而言，从它的每一个非「死胡同」分支出发进行深度优先搜索，都将会搜回到当前节点。
 *  而从它的「死胡同」分支出发进行深度优先搜索将不会搜回到当前节点。
 *  也就是说当前节点的死胡同分支将会优先于其他非「死胡同」分支入栈。
 *  
 *  这样就能保证我们可以「一笔画」地走完所有边，最终的栈中逆序地保存了「一笔画」的结果。
 *  我们只要将栈中的内容反转，即可得到答案。
 */
class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for (auto& e : tickets) {
            if (graph.find(e[0]) == graph.end())
                /* 构建优先队列, 保证每次选自然排序最小的邻居 */
                graph[e[0]] = priority_queue<string, vector<string>, greater<>>();
            graph[e[0]].push(e[1]);
        }
        dfs("JFK");
        /* 将栈中内容翻转 */
        reverse(ans.begin(), ans.end());
        return ans;
    }
private:
    vector<string> ans;
    unordered_map<string, priority_queue<string, vector<string>, greater<>>> graph;
    void dfs(const string& node) {
        if (graph.find(node) != graph.end()) {
            while (!graph[node].empty()) {
                string neighbor = graph[node].top();
                graph[node].pop();
                dfs(neighbor);
            }
        }
        /* 遍历完所有边之后才入栈 */
        ans.push_back(node);
    }
};