/* Leetcode 76.最小覆盖子串
 * 给你一个字符串 S、一个字符串 T，请在字符串 S 里面找出：包含 T 所有字母的最小子串。
 * 示例：
 * 输入: S = "ADOBECODEBANC", T = "ABC"
 * 输出: "BANC"
 * 注意, T中可以有重复的字符, 比如T = "aa", 那么S中至少要有2个‘a’才满足要求
 */
#include <map>
using namespace std;

//基本思路：
//1.初始，left指针和right指针都指向S的第一个元素.
//2.将right指针右移，扩张窗口，直到得到一个可行窗口，亦即包含T的全部字母的窗口。
//3.得到可行的窗口后，将left指针逐个右移，若得到的窗口依然可行，则更新最小窗口大小。
//4.若窗口不再可行，则跳转至2
class Solution {
public:
    string minWindow(string s, string t) {
        map<char, int> needed;  //表示窗口中, 各个字符需要多少个
        for (char c : t) needed[c]++;
        map<char, int> windows; //表示当前窗口中, 各个字符有多少个
        int l = 0, r = 0;   //左右指针
        int begin = 0, minLen = 0x7fffffff; //返回值的起始下标和长度
        //表示当前窗口中, 满足要求的字符个数
        //比如window = "aabc", t = "aaabc", 那么b, c已经满足要求, match = 2
        int match = 0;
        while (r < s.size()) {
            //expand, 移动右指针
            if (needed.find(s[r]) != needed.end()) {
                if (++windows[s[r]] == needed[s[r]])
                    match++;
            }
            r++;
            while (match == needed.size()) {
                //更新最小长度
                //因为在上一步中r++了, 所以不用r-l+1
                if (r-l < minLen) {
                    begin = l;
                    minLen = r-l;
                }
                //contract, 移动左指针
                if (needed.find(s[l]) != needed.end()) {
                    if (--windows[s[l]] < needed[s[l]])
                        match--;
                }
                l++;
            }
        }
        return minLen == 0x7fffffff ? "" : s.substr(begin, minLen);
    }
};