/* Leetcode 214.最短回文串
 * 给定一个字符串 s，你可以通过在字符串前面添加字符将其转换为回文串。找到并返回可以用这种方式转换的最短回文串。
 */
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/* 本质上就是找到以首字符为左边界的最长回文子串的右边界, 记为bound
 * 然后将bound之后的子串翻转加到s前面就行了
 */

/* 暴力法
 * 最后一个test case超时了
 */
class MyAttempt {
public:
    string shortestPalindrome(string& s) {
        int len = s.length();
        if (len < 2) return s;
        int bound = len-1;
        while (bound != 0) {
            if (isPalindrome(0, bound, s))
                break;
            bound--;
        }
        string str;
        for (int i = len-1; i > bound; i--)
            str += s[i];
        return str + s;
    }

private:
    bool isPalindrome(int i, int j, string& s) {
        while (i < j) {
            if (s[i] != s[j])
                return false;
            i++; j--;
        }
        return true;
    }
};

/* KMP算法的next数组
 * 具体参考链接中的解法五
 * https://leetcode-cn.com/problems/shortest-palindrome/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by--44/
 */
class Solution {
public:
    string shortestPalindrome(string& s) {
        string tmp = s;
        reverse(tmp.begin(), tmp.end());
        string ss = s + '#' + tmp;
        int max = getLastNext(ss);
        string sub = s.substr(max);
        reverse(sub.begin(), sub.end());
        return sub + s;
    }

private:
    /* next数组的推导在这里:
     * https://learnku.com/articles/10622/introduction-of-kmp-algorithm-and-derivation-of-next-array
     */
    int getLastNext(string& s) {
        int len = s.length();
        vector<int> next(len+1, 0);
        next[0] = -1;
        int k = 0, i = 2;
        while (i <= len) {
            if (k == -1 || s[i-1] == s[k]) {
                next[i] = k + 1;
                k++; i++;
            } else {
                k = next[k];
            }
        }
        return next[len];
    }
};

/* 类似于求最长回文子串, Leetcode 5
 * 魔改一下Manacher算法(马拉车)就行了
 * 算法的具体解释参考链接: https://www.cxyxiaowu.com/2665.html
 */
class Solution1 {
public:
    string shortestPalindrome(string& s) {
        int len = s.length();
        if (len < 2) return s;

        string str = preprocess(s);
        len = 2 * len + 1;
        /* p[i]表示以i为中心的回文串半径 */
        vector<int> p(len, 0);
        /* 当前能够回文扩散到最右下标 以及 其对应的中心下标 */
        int center = 0, maxRight = 0;
        /* 计首字符为左边界的最长回文串为s, bound是s的右边界 */
        int bound = 0;

        for (int i = 0; i < len; i++) {
            if (i < maxRight) {
                int mirror = 2 * center - i;
                /* 这一步结合链接理解 */
                p[i] = min(p[mirror], maxRight - i);
            }
            /* 尝试继续扩散 */
            int left = i - (p[i] + 1), right = i + (p[i] + 1);
            while (left >= 0 && right < len && str[left] == str[right]) {
                p[i]++;
                left--;
                right++;
            }
            /* 更新对应信息 */
            if (i + p[i] > maxRight) {
                center = i;
                maxRight = i + p[i];
            }
            /* 如果i能扩散到最左边, 更新bound */
            if (i - p[i] == 0)
                bound = max(i + p[i], bound);
        }

        string supplement;
        for (int i = len-1; i > bound; i--) {
            char c = str[i];
            if (c != '#')
                supplement += c;
        }
        return supplement + s;
    }

private:
    /* 预处理, 填充分隔符, 使得处理后的字符串长度总为奇数 */
    string preprocess(string& str) {
        string res = "#";
        for (char c : str) {
            res += c;
            res += '#';
        }
        return res;
    }
};