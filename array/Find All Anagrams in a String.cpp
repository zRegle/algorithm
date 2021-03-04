/**
 * Leetcode 438. 找到字符串中所有字母异位词
 * 给定一个字符串 s 和一个非空字符串 p，找到 s 中所有是 p 的字母异位词的子串，返回这些子串的起始索引。
 * 字符串只包含小写英文字母，并且字符串 s 和 p 的长度都不超过 20100。
 * 说明：
 *  字母异位词指字母相同，但排列不同的字符串。
 *  不考虑答案输出的顺序。
 * 示例 1:
 *  输入: s: "cbaebabacd" p: "abc"
 *  输出: [0, 6]
 *  解释:
 *   起始索引等于 0 的子串是 "cba", 它是 "abc" 的字母异位词。
 *   起始索引等于 6 的子串是 "bac", 它是 "abc" 的字母异位词。
 */
#include <string>
#include <vector>
using namespace std;

/* 滑动窗口 */

class Solution0 {
public:
    vector<int> findAnagrams(string& s, string& p) {
        vector<int> ans;
        auto window = vector<int>(26, 0);
        /* 统计p中各字母出现的频率
         * 可以理解为一个账本, 记录了s的滑动窗口的"欠账"情况 */
        for (char c : p)
            window[c - 'a']++;
        int len = s.length(), k = p.length();
        int left = 0, right = 0;
        while (left <= len - k) {
            while (right < left + k && window[s[right] - 'a'] > 0) {
                /* 字符添加到滑动窗口中, 还账 */
                window[s[right] - 'a']--;
                right++;
            }
            /* 某个字符还多了, 退出循环 */
            if (right - left == k)
                ans.push_back(left);
            /* 字符移动出滑动窗口, 欠账 */
            window[s[left] - 'a']++;
            left++;
        }
        return ans;
    }
};

class Solution1 {
public:
    vector<int> findAnagrams(string& s, string& p) {
        vector<int> ans;
        auto map = vector<int>(26, 0);
        /* 统计p中各字母出现的频率 */
        for (char c : p)
            map[c - 'a']++;
        int len = s.length(), k = p.length();
        int left = 0, right = 0;
        auto window = vector<int>(26, 0);
        while (right < len) {
            /* 将当前字符加入到滑动窗口中 */
            int charIdx = s[right] - 'a';
            window[charIdx]++;
            /* 当前滑动窗口中有多余的字母, 不断移动左指针来删除多余的字符 */
            while (window[charIdx] > map[charIdx]) {
                window[s[left] - 'a']--;
                left++;
            }
            /* 滑动窗口中没有多余的字符, 并且长度刚好等于p, 满足要求 */
            if (right - left == k - 1)
                ans.push_back(left);
            right++;
        }
        return ans;
    }
};