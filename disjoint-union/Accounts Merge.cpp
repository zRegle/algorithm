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
 * 
 * 提示：
 *  accounts的长度将在[1，1000]的范围内。
 *  accounts[i]的长度将在[1，10]的范围内。
 *  accounts[i][j]的长度将在[1，30]的范围内。
 */
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

/* accounts长度在[1, 1000], accounts[i]长度在[1, 10]
 * 那么最多会有1000 * 10 = 10000个email
 */
#define ARRAY_SIZE 10000

/**
 * 可以将每个email看成是一个节点, 同一个账户里的email两两相连
 * 就可以转化为提取连通分量的问题, 可以使用并查集
 */

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            father[i] = i;
            rank[i] = 1;
        }
        /* email -> ID的映射 */
        unordered_map<string, int> mail2ID;
        /* email -> 用户名的映射 */
        unordered_map<string, string> mail2Name;
        int id = 0;
        for (auto& a : accounts) {
            for (int i = 1; i < a.size(); i++) {
                if (mail2ID.find(a[i]) == mail2ID.end()) {
                    mail2ID[a[i]] = id++;
                    mail2Name[a[i]] = a[0];
                }
                /* 统一跟account的第一个email进行merge
                 * 不需要再跟account的其他email merge了
                 */
                merge(mail2ID[a[1]], mail2ID[a[i]]);
            }
        }
        /* ID -> (用户名 + 连通分量)的映射 */
        unordered_map<int, vector<string>> ID2comp;
        for (auto& p : mail2ID) {
            const string& mail = p.first;
            /* 找到这个email属于哪个连通分量 */
            int father = find(mail2ID[mail]);
            if (ID2comp.find(father) == ID2comp.end()) {
                ID2comp[father] = vector<string>();
                /* 返回结果账号的第一个元素是用户名 */
                ID2comp[father].push_back(mail2Name[mail]);
            }
            /* 为这个email对应的连通分量添加email */
            ID2comp[father].push_back(mail);
        }
        vector<vector<string>> ans;
        /* 对各个连通分量进行排序 */
        for (auto& p : ID2comp) {
            auto& componet = p.second;
            sort(componet.begin() + 1, componet.end());
            ans.push_back(componet);
        }
        return ans;
    }
private:
    /* 并查集模板 */
    int father[ARRAY_SIZE];
    int rank[ARRAY_SIZE];

    int find(int x) {
        return father[x] == x ? x : (father[x] = find(father[x]));
    }

    void merge(int i, int j) {
        int x = find(i), y = find(j);
        if (x == y) return;
        if (rank[x] >= rank[y]) 
            father[y] = x;
        else
            father[x] = y;
        if (rank[x] == rank[y])
            rank[x]++;
    }
};