/* Leetcode 131.分割回文串
 * 给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。
 * 返回 s 所有可能的分割方案。
 * 示例:
 *  输入: "aab"
 *  输出:
 *   [
 *    ["aa","b"],
 *    ["a","a","b"]
 *   ]
 */
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<string> curPartition;
        string tmp;
        dfs(tmp, 0, curPartition, tmp);
        return ans;
    }
private:
    vector<vector<string>> ans;
    /**
     * dfs生成所有合适的回文串分割
     * @param str 原字符串
     * @param idx 当前递归到的字符下标, 即搜索深度
     * @param curPartition 当前的分割方式
     * @param tmp 下一个准备形成的回文串
     * 例如: str = "sccsabba", idx = 7,curPartition = {"sccs"}, tmp = "abb",
     * 因为我们之前将"sccs"切作一个回文串, 那么接下来的回文串就不能出现"sccs", tmp = "abb"
     */
    void dfs(string& str, int idx, vector<string>& curPartition, string& tmp) {
        if (idx < str.size()) {
            tmp += str[idx];
            if (isPalindrome(tmp)) {
                //tmp已经可以形成一个回文串
                curPartition.push_back(tmp);
                string copy = tmp; //保存现场
                tmp = ""; //tmp置空, 用于形成一个回文串
                dfs(str, idx+1, curPartition, tmp);
                tmp = copy; //回溯复原
                curPartition.pop_back();
            }
            //这里有两种情况:
            //1.tmp不能形成回文串, 继续dfs尝试构成合法分割
            //2.tmp可以形成回文串, 但不选择分割, 继续dfs尝试构成合法分割
            dfs(str, idx+1, curPartition, tmp);
        } else {
            //如果原字符串遍历完后, tmp依然无法形成回文串
            //即tmp中有残留字符(如果tmp是回文串, 那么在上一层已经被置空)
            //则代表这次的dfs分割不合法, 反之则合法
            if (tmp.empty())
                ans.push_back(curPartition);
        }
    }

    //判断是否为回文串
    inline bool isPalindrome(string& s) {
        int l = 0, r = s.size()-1;
        while (l < r) {
            if (s[l++] != s[r--])
                return false;
        }
        return true;
    }
};

int main() {
    string str = "aab";
    Solution sol;
    auto ans = sol.partition(str);
    for (vector<string>& p : ans) {
        for (const string& s : p)
            cout<<s<<" ";
        cout<<endl;
    }
    return 0;
}