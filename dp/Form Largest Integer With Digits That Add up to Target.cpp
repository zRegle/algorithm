/**
 * Leetcode 1449. 数位成本和为目标值的最大数字
 * 给你一个整数数组 cost 和一个整数 target 。请你返回满足如下规则可以得到的 最大 整数：
 *  (1)给当前结果添加一个数位（i + 1）的成本为 cost[i] （cost 数组下标从 0 开始）。
 *  (2)总成本必须恰好等于 target 。
 *  (3)添加的数位中没有数字 0 。
 * 由于答案可能会很大，请你以字符串形式返回。
 * 如果按照上述要求无法得到任何整数，请你返回 "0" 。
 *
 * 示例 1：
 *  输入：cost = [4,3,2,5,6,7,2,5,5], target = 9
 *  输出："7772"
 *  解释：添加数位 '7' 的成本为 2 ，添加数位 '2' 的成本为 3 。所以 "7772" 的代价为 2*3+ 3*1 = 9 。
 *       "977" 也是满足要求的数字，但 "7772" 是较大的数字。
 *       数字     成本
 *       1  ->   4
 *       2  ->   3
 *       3  ->   2
 *       4  ->   5
 *       5  ->   6
 *       6  ->   7
 *       7  ->   2
 *       8  ->   5
 *       9  ->   5
 *
 * 示例 2：
 *  输入：cost = [7,6,5,5,5,6,8,7,8], target = 12
 *  输出："85"
 *  解释：添加数位 '8' 的成本是 7 ，添加数位 '5' 的成本是 5 。"85" 的成本为 7 + 5 = 12 。
 *
 * 示例 3：
 *  输入：cost = [2,4,6,2,4,6,4,4,4], target = 5
 *  输出："0"
 * 解释：总成本是 target 的条件下，无法生成任何整数。
 *
 * 示例 4：
 *  输入：cost = [6,10,15,40,40,40,40,40,40], target = 47
 *  输出："32211"
 *
 * 提示：
 *  (1)cost.length == 9
 *  (2)1 <= cost[i] <= 5000
 *  (3)1 <= target <= 5000
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/**
 * 将每个数字的cost看成重量, 每个数字的大小看成价值
 * target看成背包容量, 可以转化为完全背包问题
 * 不同点在于背包容量要恰好用完, 并且价值比较函数有点特别
 */
class Solution0 {
public:
    string largestNumber(vector<int>& cost, int target) {
        vector<vector<string>> dp(10, vector<string>(target+1));
        /* 不拿任何物品就不会占用背包容量, 将不可能的状态全部初始化为非法状态 */
        fill(dp[0].begin(), dp[0].end(), "#");
        dp[0][0] = "";
        for (int i = 0; i <= 9; i++) {
            int c = cost[i-1];
            for (int j = 0; j <= target; j++) {
                dp[i][j] = dp[i-1][j];
                /* 必须要从合法状态转移, 代表背包容量恰好用完 */
                if (j >= c && dp[i][j-c] != "#")
                    /* 注意这里, i是从小到大遍历的
                     * 为了使结果代表的数字尽可能地大, 物品的价值应该头插入
                     * 因为dp[i][j-c]包含的数字肯定不大于i
                     * (不能从倒序遍历i, 因为dp[i][j]依赖于dp[i-1][j])
                     */
                    dp[i][j] = max(dp[i][j], (char)('0' + i) + dp[i][j-c], cmp);
            }
        }
        return dp[9][target] != "#" ? dp[9][target] : "0";
    }

private:
    /* 价值比较函数 */
    static bool cmp(const string& s1, const string& s2) {
        size_t l1 = s1.length(), l2 = s2.length();
        /* 长度不一样, 长度较长的字符串代表更大的数字 */
        if (l1 != l2)
            return l1 < l2;
        /* 长度一样, 字典序比较 */
        return s1 < s2;
    }
    string optimize(vector<int>& cost, int target) {
        vector<string> dp(target+1, "#");
        dp[0] = "";
        /* i倒序遍历, 物品价值就可以尾插入 */
        for (int i = 9; i >= 1; i--) {
            int c = cost[i-1];
            for (int j = c; j <= target; j++) {
                dp[j] = max(dp[j], dp[j-c] + (char)('0' + i), cmp);
            }
        }
        return dp[target] != "#" ? dp[target] : "0";
    }
};

/**
 * 第二种dp思路, 将每个数字的价值都看成1(每次选择数字都会使结果长度加一)
 * 最后反推出选择的数字方案
 * 优势在于: 时间复杂度不变, 没有过多的字符串操作
 */
class Solution1 {
public:
    string largestNumber(vector<int>& cost, int target) {
        vector<vector<int>> dp(10, vector<int>(target+1));
        /* 记录dp的转移路径 */
        vector<vector<int>> from(10, vector<int>(target+1));
        /* 初始化非法状态 */
        fill(dp[0].begin(), dp[0].end(), -1);
        dp[0][0] = 0;
        for (int i = 1; i <= 9; i++) {
            int c = cost[i-1];
            for (int j = 0; j <= target; j++) {
                dp[i][j] = dp[i-1][j];
                from[i][j] = j;
                if (j >= c && dp[i][j-c] >= 0) {
                    /* 注意这里要≤, 因为从dp[i][j-c]转移可以使结果长度加一 */
                    if (dp[i-1][j] <= dp[i][j-c] + 1) {
                        dp[i][j] = dp[i][j-c] + 1;
                        from[i][j] = j-c;
                    }
                }
                /* 不需要记录从i-1还是i转移
                 * 因为如果from[i][j] == j, 必定从dp[i-1][j]转移
                 * 反之亦然 */
            }
        }
        if (dp[9][target] == -1) return "0";
        string ans;
        int i = 9, j = target;
        /* 反推数字, i倒序遍历, 数字较大的排在字符串前面 */
        while (i > 0) {
            if (from[i][j] == j)
                i--;
            else {
                ans += (char)('0' + i);
                j = from[i][j];
            }
        }
        return ans;
    }

private:
    string optimize(vector<int>& cost, int target) {
        vector<int> dp(target+1, -1);
        dp[0] = 0;
        for (int c : cost) {
            for (int j = c; j <= target; j++) {
                if (dp[j-c] >= 0)
                    dp[j] = max(dp[j], dp[j-c] + 1);
            }
        }
        if (dp[target] == -1) return "0";
        string ans;
        int i = 9, j = target;
        while (i > 0) {
            int c = cost[i-1];
            if (j >= c && dp[j] == dp[j-c] + 1) {
                ans += (char)('0' + i);
                j -= c;
            } else {
                i--;
            }
        }
        return ans;
    }
};