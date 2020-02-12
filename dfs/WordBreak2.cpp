/* Leetcode 140.单词拆分2
 * 给定一个非空字符串s和一个包含非空单词列表的字典wordDict.
 * 在字符串中增加空格来构建一个句子,使得句子中所有的单词都在词典中.返回所有这些可能的句子.
 * 示例 1：
 *  输入:
 *   s = "catsanddog"
 *   wordDict = ["cat", "cats", "and", "sand", "dog"]
 *  输出:
 *   [
 *    "cats and dog",
 *    "cat sand dog"
 *   ]
 */
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        if (s.empty()) {
            ans.emplace_back("");
            return ans;
        }
        if (wordDict.empty())
            return ans;
        auto cmp = [](string& s1, string& s2) ->
                bool {return s1.length() < s2.length();};
        auto it = max_element(wordDict.begin(), wordDict.end(), cmp);
        int maxLen = it->length();
        string tmp;
        dfs(0, s, tmp, maxLen, wordDict);
        return ans;
    }
private:
    vector<string> ans;
    //记忆化map, 例如键值对<2, false>, 表示从下标2出发, 不能拆分单词
    //键值对<3, true>, 表示从下标3出发, 能拆分单词
    unordered_map<int, bool> map;
    bool dfs(int idx, string& s, string& tmp, int maxLen, vector<string>& dict) {
        if (idx == s.length()) {
            tmp.pop_back(); //把上一层加进去的空格pop出来
            ans.push_back(tmp);
            return true;
        }
        auto it = map.find(idx);
        if (it != map.end()) {
            if (!it->second)
                //从这个下标出发不能拆分单词, 不用继续dfs了
                return false;
        }
        bool flag = false;
        for (int i = 1; i <= maxLen && idx + i <= s.length(); i++) {
            string str = s.substr(idx, i);
            if (find(dict.begin(), dict.end(), str) != dict.end()) {
                string copy = tmp; //保存现场
                tmp += str;
                tmp.push_back(' ');
                if (dfs(idx+i, s, tmp, maxLen, dict))
                    flag = true;
                tmp = copy; //回溯复原
            }
        }
        return map[idx] = flag;
    }
};