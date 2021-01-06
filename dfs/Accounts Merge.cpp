/**
 * Leetcode 721. 账户合并
 * 给定一个列表 accounts，每个元素 accounts[i] 是一个字符串列表，
 * 其中第一个元素 accounts[i][0] 是 名称 (name)，其余元素是 emails 表示该账户的邮箱地址。
 * 
 * 现在，我们想合并这些账户。如果两个账户都有一些共同的邮箱地址，则两个账户必定属于同一个人。
 * 请注意，即使两个账户具有相同的名称，它们也可能属于不同的人，因为人们可能具有相同的名称。
 * 一个人最初可以拥有任意数量的账户，但其所有账户都具有相同的名称。
 * 合并账户后，按以下格式返回账户：每个账户的第一个元素是名称，其余元素是按顺序排列的邮箱地址。
 * 账户本身可以以任意顺序返回。
 *  
 * 示例 1：
 * 输入：
 *  accounts = [["John", "johnsmith@mail.com", "john00@mail.com"], 
 *              ["John", "johnnybravo@mail.com"], 
 *              ["John", "johnsmith@mail.com", "john_newyork@mail.com"], 
 *              ["Mary", "mary@mail.com"]]
 * 输出：
 *  [["John", 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com'],  
 *   ["John", "johnnybravo@mail.com"], 
 *   ["Mary", "mary@mail.com"]]
 * 解释：
 *  第一个和第三个 John 是同一个人，因为他们有共同的邮箱地址 "johnsmith@mail.com"。 
 *  第二个 John 和 Mary 是不同的人，因为他们的邮箱地址没有被其他帐户使用。
 *  可以以任何顺序返回这些列表，例如答案 [['Mary'，'mary@mail.com']，['John'，'johnnybravo@mail.com']，
 *  ['John'，'john00@mail.com'，'john_newyork@mail.com'，'johnsmith@mail.com']] 也是正确的。
 */
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

/**
 * 可以将每个email看成是一个节点, 同一个账户里的email两两相连
 * 就可以转化为提取连通分量的问题, 可以用dfs方法
 */

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        /* 构建邻接矩阵, 节点邻居列表的第一个元素用来保存用户名, 其余为邻居节点 */
        for (auto& a : accounts) {
            int size = a.size();
            for (int i = 1; i < size; i++) {
                if (graph.find(a[i]) == graph.end()) {
                    graph[a[i]] = vector<string>();
                    /* 第一个元素保存用户名 */
                    graph[a[i]].push_back(a[0]);
                }
                /* 统一认为这个email与account的第一个email相连
                 * 那么这个email就跟account的其他email连通了
                 * 已经足够求连通分量了
                 */
                graph[a[i]].push_back(a[1]);
                graph[a[1]].push_back(a[i]);
            }
        }
        for (auto& p : graph) {
            const string& node = p.first;
            if (vis.find(node) == vis.end()) {
                vis.insert(node);
                vector<string> component;
                /* 填入用户名 */
                component.push_back(p.second[0]);
                dfs(node, component);
                /* 对剩下的email进行排序 */
                sort(component.begin() + 1, component.end());
                ans.push_back(component);
            }
        }
        return ans;
    }
private:
    vector<vector<string>> ans;
    unordered_map<string, vector<string>> graph; /* 邻接矩阵 */
    unordered_set<string> vis; /* dfs的标记数组 */

    void dfs(const string& node, vector<string>& componet) {
        /* 添加到当前连通分量 */
        componet.push_back(node);
        int cnt = graph[node].size();
        /* 节点邻居列表的第一个元素是用户名, 所以跳过 */
        for (int i = 1; i < cnt; i++) {
            if (vis.find(graph[node][i]) == vis.end()) {
                vis.insert(graph[node][i]);
                dfs(graph[node][i], componet);
            }
        }
    }
};