/**
 * Leetcode 151. 翻转字符串里的单词
 * 给定一个字符串，逐个翻转字符串中的每个单词。
 * 
 * 说明：
 *  (1)无空格字符构成一个 单词 。
 *  (2)输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。
 *  (3)如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。
 * 
 * 示例 1：
 *  输入："the sky is blue"
 *  输出："blue is sky the"
 * 
 * 示例 2：
 *  输入："  hello world!  "
 *  输出："world! hello"
 *  解释：输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。
 * 
 * 示例 3：
 *  输入："a good   example"
 *  输出："example good a"
 *  解释：如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。
 * 
 * 示例 4：
 *  输入：s = "  Bob    Loves  Alice   "
 *  输出："Alice Loves Bob"
 * 
 * 示例 5：
 *  输入：s = "Alice does not even like bob"
 *  输出："bob like even not does Alice"
 * 
 * 提示：
 *  (1)1 <= s.length <= 104
 *  (2)s 包含英文大小写字母、数字和空格 ' '
 *  (3)s 中 至少存在一个 单词
 * 
 * 进阶：
 * 请尝试使用 O(1) 额外空间复杂度的原地解法。
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/* 思路: 先将整个字符串翻转, 然后再对每一个单词翻转 */
class Solution {
public:
    string reverseWords(string& s) {
        reverse(s.begin(), s.end());
        int n = s.length();
        int start = 0, end = s.length()-1;
        /* 去除开头多余的空格 */
        while (start < n && s[start] == ' ') start++;
        /* 去除结尾多余的空格 */
        while (end >= 0 && s[end] == ' ') end--;
        if (start >= end) return "";
        int l = start;
        while (l <= end) {
            /* 单词间可能有多余的空格, 暂时跳过 */
            while (l <= end && s[l] == ' ') l++;
            /* 将单词翻转 */
            int r = l;
            while (r <= end && s[r] != ' ') r++;
            reverse(s.begin() + l, s.begin() + r);
            /* 寻找下一个空格 */
            l = r;
        }
        /* 去除单词间多余的空格 */
        int tail = start;
        for (int i = start; i <= end; i++) {
            if (i >= 0 && s[i] == ' ' && s[i-1] == ' ') continue;
            s[tail++] = s[i];
        }
        return s.substr(start, tail - start);
    }
};