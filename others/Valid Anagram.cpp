/* Leetcode 242.有效的字母异位词
 * 给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。
 * 示例1
 *  输入: s = "anagram", t = "nagaram
 *  输出: true
 */
#include <string>
using namespace std;

/* 哈希表统计 */
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) return false;
        uint32_t map[26] = {0};
        for (char c : s) {
            map[c - 'a']++;
        }
        for (char c : t) {
            if (map[c - 'a'] == 0)
                return false;
            map[c - 'a']--;
        }
        return true;
    }
};