/* Leetcode 343.正数拆分
 * 给定一个正整数 n，将其拆分为至少两个正整数的和,并使这些整数的乘积最大化.返回你可以获得的最大乘积.
 * 示例 1:
 *  输入: 2
 *  输出: 1
 * 解释: 2 = 1 + 1, 1 × 1 = 1。
 * 示例 2:
 *  输入: 10
 *  输出: 36
 * 解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36。
 * 说明: 你可以假设n不小于2且不大于 58.
 */
#include <vector>
#include <cmath>
using namespace std;

//最初想法:
//dp[i]表示拆分正整数i的最大乘积
int mySolution(int n) {
    if (n <= 3) return n - 1; //edge case
    vector<int> dp(n + 1, 0);
    dp[2] = 2; dp[3] = 3;
    for (int i = 4; i <= n; i++) {
        for (int j = 1; j <= i / 2; j++) {
            dp[i] = max(dp[i], dp[j] * dp[i - j]);
        }
    }
    return dp[n];
}

//dp[i]表示将正整数i拆分成至少两个正整数的和之后，这些正整数的最大乘积
class Solution {
public:
    int integerBreak(int n) {
        vector<int> dp(n+1, 0);
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= i/2; j++) {
                //i分成两部分, 第一部分是j, 第二部分是i-j
                //将i拆成j和i-j之后, i-j继续拆分成多个整数(j*dp[i-j])
                //将i拆成j和i-j之后, i-j不继续拆分(j*(i-j))
                dp[i] = max(dp[i], max(j * (i-j), j * dp[i-j]));
            }
        }
        return dp[n];
    }
};

//贪心算法, 尽量将数拆分成3, 剩余的部分尽量拆成2
//当n = 2时, 不拆分最优
//当n = 3时, 不拆分最优
//当n = 4时, 拆成2x2
//当n = 5时, 拆成2x3
//当n = 6时, 拆成3x3
int integerBreak(int n) {
    if (n < 4) 
        return n-1;
    int a = n / 3, b = n % 3;
    if (b == 0)
        //整除3, 全部拆成3
        return int(pow(3, a));
    else if (b == 1)
        //余1, 抽1个3出来和剩余的1组合成4
        return int(pow(3, a-1) * 4);
    else
        //余2, 不拆2
        return int(pow(3, a) * 2);
}