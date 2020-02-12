#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * leetcode 139. Word Break
 * 给定一个字符串和一个字典, 问该字符串是否可由字典中的单词组成(单词可重复使用)
 * 例如:
 * s = "applepenapple", wordDict = ["apple", "pen"] => true
 * s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"] => false
 */

/*
 * bfs方法:
 * 可以看成一个图的问题, 顶点的值是字符串中的第i个字符, 边是字典中的单词
 * 我们的目标是在图中寻找一条路径, 能否从初始顶点走到最终的顶点
 * 例如: s = "leetcode", wordDict = ["leet", "code"]
 * 那么我们有路径0->4->8
 */
//还有dfs和dp的方法, 参考对应的文件夹
class Solution {
public:
    bool wordBreak(string& s, vector<string>& wordDict) {
        if (s.empty()) return true;
        if (wordDict.empty()) return false;
        auto cmp = [](const string& s1, const string& s2) ->
                bool {return s1.length() < s2.length();};
        auto it = max_element(wordDict.begin(), wordDict.end(), cmp);
        int maxLen = it->length(); //获取字典中最长单词的长度, 剪枝
        queue<int> q;
        q.push(0);
        vector<bool> visited(s.length(), false); //是否已经到达过某个位置
        while (!q.empty()) {
            //当前深度要从哪里开始出发截取字符串
            int idx = q.front(); q.pop();
            for (int i = 1; i <= maxLen && idx + i <= s.length(); i++) {
                string word = s.substr(idx, i);
                if (find(wordDict.begin(), wordDict.end(), word) != wordDict.end()) {
                    if (idx + i == s.length())
                        return true;
                    if (!visited[idx + i]) {
                        visited[idx + i] = true;
                        q.push(idx + i);
                    }
                }
            }
        }
        return false;
    }
};

int main() {
    string str = "bccdbacdbdacddabbaaaadababadad";
    vector<string> wordDict
            ({"cbc","bcda","adb","ddca","bad",
             "bbb","dad","dac","ba","aa","bd",
             "abab","bb","dbda","cb","caccc","d",
             "dd","aadb","cc","b","bcc","bcd","cd",
             "cbca","bbd","ddd","dabb","ab","acd",
             "a","bbcc","cdcbd","cada","dbca","ac",
             "abacd","cba","cdb","dbac","aada","cdcda",
             "cdc","dbc","dbcb","bdb","ddbdd","cadaa",
             "ddbc","babb"});
    Solution s;
    cout<<s.wordBreak(str, wordDict)<<endl;
    return 0;
}