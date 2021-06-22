/**
 * Leetcode 1239. 串联字符串的最大长度
 * 给定一个字符串数组 arr，字符串 s 是将 arr 某一子序列字符串连接所得的字符串，
 * 如果 s 中的每一个字符都只出现过一次，那么它就是一个可行解。
 * 请返回所有可行解 s 中最长长度。
 *
 * 示例 1：
 *  输入：arr = ["un","iq","ue"]
 *  输出：4
 *  解释：所有可能的串联组合是 "","un","iq","ue","uniq" 和 "ique"，最大长度为 4。
 * 示例 2：
 *  输入：arr = ["cha","r","act","ers"]
 *  输出：6
 *  解释：可能的解答有 "chaers" 和 "acters"。
 * 示例 3：
 *  输入：arr = ["abcdefghijklmnopqrstuvwxyz"]
 *  输出：26
 *
 * 提示：
 *  (1)1 <= arr.length <= 16
 *  (2)1 <= arr[i].length <= 26
 *  (3)arr[i] 中只含有小写英文字母
 */
#include <string>
#include <vector>
#include <bitset>
using std::vector;
using std::string;
using std::bitset;
using std::max;

/* 简单的dfs + 回溯 */
class Solution {
public:
    int maxLength(vector<string>& arr) {
        n = arr.size();
        valid.resize(n, 1);
        /* 先去除本身含重复字母的字符串 */
        for (int i = 0; i < n; i++) {
            string& s = arr[i];
            for (char c : s) {
                if (bitmap[c - 'a']) {
                    valid[i] = false;
                    break;
                }
                bitmap.set(c - 'a');
            }
            bitmap.reset();
        }
        return dfs(0, 0, arr);
    }

private:
    int n;
    vector<int> valid; /* 字符串本身不含重复字母的集合 */
    bitset<26> bitmap;
    int dfs(int idx, int length, vector<string>& arr) {
        if (bitmap.all() || idx == n)
            return length;
        if (valid[idx] == false)
            /* 字符串本身含重复字母, 跳过 */
            return dfs(idx+1, length, arr);
        int pick = 0, skip = 0;
        string& cur = arr[idx];
        int i, j, len = cur.length();
        /* 判断字符串是否跟之前选择的字符串是否有重复字母 */
        for (i = 0; i < len; i++) {
            if (bitmap[cur[i] - 'a'])
                break;
            bitmap.set(cur[i] - 'a');
        }
        if (i == cur.length())
            /* 字符串跟之前的不冲突 */
            pick = dfs(idx+1, length + len, arr);
        for (j = 0; j < i; j++)
            /* 回溯 */
            bitmap.reset(cur[j] - 'a');
        skip = dfs(idx+1, length, arr);
        return max(pick, skip);
    }
};