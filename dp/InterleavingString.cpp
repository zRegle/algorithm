#include <iostream>
using namespace std;

/*
 * leetcode 97
 * 给定字符串s1, s2, s3, 判断s3是否可由将s2的字符按顺序插入s1中形成
 * Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
 * Output: true
 * Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
 * Output: false
 * 
 * 思路:
 * dp[i][j]表示将s2的前j个字符插入s1的前i个字符中, 能否构成s3中前i+j个字符
 */

class Solution {
public:
    bool isInterleave(string& s1, string& s2, string& s3) {
        int len1 = s1.length(), len2 = s2.length(), len3 = s3.length();
        if (len1 + len2 != len3) return false;
        bool** dp = new bool*[len1+1];
        for (int i = 0; i <= len1; ++i) dp[i] = new bool[len2+1]();
        //i, j分别代表用到了s1, s2的第几个字符
        for (int i = 0; i <= len1; ++i) {
            for (int j = 0; j <= len2; ++j) {
                if (i == 0 && j == 0) dp[0][0] = true;
                else if (i == 0) dp[0][j] = s2[j-1] == s3[j-1] && dp[0][j-1];
                else if (j == 0) dp[i][0] = s1[i-1] == s3[i-1] && dp[i-1][0];
                //可以从s1中拿或者从s2中拿
                else dp[i][j] = (s1[i-1] == s3[i+j-1] && dp[i-1][j]) || (s2[j-1] == s3[i+j-1] && dp[i][j-1]);
            }
        }
        bool res = dp[len1][len2];
        for (int i = 0; i <= len1; ++i) delete[](dp[i]);
        delete[](dp);
        return res;
    }
};

int main() {
   string s1 = "aabcc";
   string s2 = "dbbca";
   string s3 = "aadbbcbcac";
   auto s = new Solution();
   cout<<s->isInterleave(s1, s2, s3)<<endl;
}