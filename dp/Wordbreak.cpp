/* Leetcode 139.单词拆分
 * 给定一个非空字符串s和一个包含非空单词列表的字典wordDict，判定s是否可以被空格拆分为一个或多个在字典中出现的单词。
 * 说明：
 *  拆分时可以重复使用字典中的单词。
 *  你可以假设字典中没有重复的单词。
 * 示例 1：
 *  输入: s = "leetcode", wordDict = ["leet", "code"]
 *  输出: true
 *  解释: 返回 true 因为 "leetcode" 可以被拆分成 "leet code"。
 * 示例 3：
 *  输入: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
 *  输出: false
 */
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//dp, 还有dfs和bfs的做法, 请参考对应的文件夹
class DP {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int len = s.length();
        vector<bool> dp(len+1, false); //dp[i]表示前i个字符能否拆分
        dp[0] = true;
        for (int i = 1; i <= len; i++) {
            for (int j = 1; j <= i; j++) {
                string str = s.substr(j-1, i-j+1);
                if (find(wordDict.begin(), wordDict.end(), str) != wordDict.end()) {
                    if ((dp[i] = dp[j-1]))
                        //如果前i个字符能够拆分, 就进行下一次外层循环
                        //不要让后面的内层循环覆盖掉正确的答案
                        break;
                }
            }
        }
        return dp[len];
    }
};