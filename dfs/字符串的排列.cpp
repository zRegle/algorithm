/**
 * 剑指 Offer 38. 字符串的排列
 * 输入一个字符串，打印出该字符串中字符的所有排列。
 * 你可以以任意顺序返回这个字符串数组，但里面不能有重复元素。
 *
 * 示例:
 *  输入：s = "abc"
 *  输出：["abc","acb","bac","bca","cab","cba"]
 */
#include <vector>
#include <string>
#include <unordered_set>
using std::vector;
using std::string;
using std::unordered_set;
using std::swap;

/**
 * 与leetcdoe 47一样, 介绍一下另外一种dfs思路
 * 通过字符交换，先固定第1位字符（n种情况）、再固定第2位字符（n-1种情况）、...、
 * 最后固定第n位字符（1种情况）。
 * 当字符串存在重复字符时，排列方案中也存在重复的排列方案。
 * 为排除重复方案，需在固定某位字符时，保证 “每种字符只在此位固定一次” ，
 * 即遇到重复字符时不交换，直接跳过
 */
class Solution {
public:
    vector<string> permutation(string s) {
        dfs(0, s);
        return ans;
    }

private:
    vector<string> ans;
    void dfs(int idx, string& s) {
        if (idx == s.length()) {
            ans.push_back(s);
            return;
        }
        unordered_set<char> set;
        for (int i = idx; i < s.length(); i++) {
            if (set.find(s[i]) != set.end()) continue;
            set.insert(s[i]);
            swap(s[idx], s[i]);
            dfs(idx+1, s);
            swap(s[idx], s[i]);
        }
    }
};