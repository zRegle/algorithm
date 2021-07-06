/**
 * Leetcode 451. 根据字符出现频率排序
 * 给定一个字符串，请将字符串里的字符按照出现的频率降序排列。
 * 
 * 示例 1:
 * 输入: "tree"
 * 输出: "eert"
 * 解释: 'e'出现两次，'r'和't'都只出现一次。
 *       因此'e'必须出现在'r'和't'之前。此外，"eetr"也是一个有效的答案。
 * 
 * 示例 2:
 * 输入: "cccaaa"
 * 输出: "cccaaa"
 * 解释: 'c'和'a'都出现三次。此外，"aaaccc"也是有效的答案。
 *       注意"cacaca"是不正确的，因为相同的字母必须放在一起。
 * 
 * 示例 3:
 * 输入: "Aabb"
 * 输出: "bbAa"
 * 解释: 此外，"bbaA"也是一个有效的答案，但"Aabb"是不正确的。
 *       注意'A'和'a'被认为是两种不同的字符。
 */
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

/* 哈希表 + 大顶堆解决 */
class Solution {
public:
    string frequencySort(string s) {
        if (s.empty()) return "";
        unordered_map<char, int> freq;
        /* 统计频率 */
        for (char c : s) {
            if (freq.count(c) == 0)
                freq[c] = 0;
            freq[c]++;
        }
        /* 根据频率排序 */
        auto cmp = [&freq](char c1, char c2) -> bool {
            return freq[c1] < freq[c2];
        };
        priority_queue<char, vector<char>, decltype(cmp)> q(cmp);
        for (auto& p : freq) {
            q.push(p.first);
        }
        /* 输出结果 */
        int i = 0;
        while (!q.empty()) {
            char c = q.top(); q.pop();
            int k = freq[c];
            while (k--) s[i++] = c;
        }
        return s;
    }
};