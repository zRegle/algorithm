/* Leetcode 139.单词拆分
 * 给定一个非空字符串s和一个包含非空单词列表的字典wordDict，判定s是否可以被空格拆分为一个或多个在字典中出现的单词。
 * 说明：
 *  拆分时可以重复使用字典中的单词。
 *  你可以假设字典中没有重复的单词。
 * 示例 1：
 *  输入: s = "leetcode", wordDict = ["leet", "code"]
 *  输出: true
 *  解释: 返回 true 因为 "leetcode" 可以被拆分成 "leet code"。
 * 示例 3：
 *  输入: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
 *  输出: false
 */
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
using namespace std;

//dfs, 还有bfs和dp的做法, 请参考对应的文件夹
class DFS {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        if (s.empty()) return true;
        if (wordDict.empty()) return false;
        auto cmp = [](const string& s1, const string& s2) ->
                bool {return s1.length() < s2.length();};
        auto it = max_element(wordDict.begin(), wordDict.end(), cmp);
        int maxLen = it->length(); //记录字典中最长单词长度, 用于剪枝
        return dfs(0, s, wordDict, maxLen);
    }
private:
    //记忆化map, 从key出发, 能否拆分
    unordered_map<int, bool> map;
    /**
     * 从idx出发, 能否将词拆分
     * @param idx 当前深度要从哪里开始截取字符串
     * @param s 源字符串
     * @return true or false
     */
    bool dfs(int idx, string& s, vector<string>& dict, int maxLen) {
        if (idx == s.length())
            return true;
        else if (map.find(idx) != map.end())
            return map[idx];
        else {
            for (int i = 1; i <= maxLen && idx + i <= s.length(); i++) {
                string str = s.substr(idx, i-idx+1);
                if (find(dict.begin(), dict.end(), str) != dict.end()) {
                    if (dfs(i+1, s, dict, maxLen))
                        return map[idx] = true;
                }
            }
            return map[idx] = false;
        }
    }
};