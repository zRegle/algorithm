/* Leetcode 44.通配符匹配
 * 给定一个字符串 (s) 和一个字符模式 (p) ，实现一个支持 '?' 和 '*' 的通配符匹配。
 * '?' 可以匹配任何单个字符。
 * '*' 可以匹配任意字符串（包括空字符串）。
 * 两个字符串完全匹配才算匹配成功。
 */

#include <iostream>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int s_l = s.length(), p_l = p.length();
        //i: s的当前指针
        //j: p的当前指针
        //starIdx: '*'在p里的位置
        //match: 用于记录'*'匹配了多少个s的字符
        int i = 0, j = 0, starIdx = -1, match = -1;
        while (i < s_l) {
            char s_cur = s[i], p_cur = p[j];
            if (j < p_l && (s_cur == p_cur || p_cur == '?')) {
                i++;
                j++;
            } else if (p_cur == '*') {
                starIdx = j;    //记录'*'的位置
                //下面这两行代码表示'*'匹配空字符串
                match = i;
                j++;
            } else if (starIdx != -1) {
                j = starIdx + 1;    //回退到'*'的下一个字符
                match++;    //匹配了s的一个字符
                i = match;
            } else
                return false;
        }
        if (i == s_l && j == p_l)
            return true;
        else if (i == s_l) {
            //s已经到头, p没到头, 检查p剩下的是否全为'*'
            for (; j < p_l; j++)
                if (p[j] != '*')
                    return false;
            return true;
        } else
            return false;
    }
};