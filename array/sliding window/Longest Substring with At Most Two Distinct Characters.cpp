/**
 * Leetcode 159. 至多包含两个不同字符的最长子串
 * 给定一个字符串 s ，找出 至多 包含两个不同字符的最长子串 t ，并返回该子串的长度。
 * 
 * 示例 1:
 *  输入: "eceba"
 *  输出: 3
 *  解释: t 是 "ece"，长度为3。
 * 示例 2:
 *  输入: "ccaabbb"
 *  输出: 5
 *  解释: t 是 "aabbb"，长度为5。
 */
#include <string>
using namespace std;

class Solution0 {
public:
    int lengthOfLongestSubstringTwoDistinct(string& s) {
        int left = 0, right = 0; /* 滑动窗口 */
        int cnt = 0; /* 当前窗口的不同字符个数 */
        int ans = 0;
        int map[128] = {0}; /* 哈希表, 统计字符出现的次数 */
        while (right < s.length()) {
            if (map[s[right]] == 0)
                /* s[right]是当前窗口里的新字符 */
                cnt++;
            map[s[right]]++;
            /* 不同字符个数超过2, 调整左指针 */
            while (cnt > 2) {
                map[s[left]]--;
                if (map[s[left]] == 0)
                    /* 窗口中少了一种字符串 */
                    cnt--;
                left++;
            }
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};