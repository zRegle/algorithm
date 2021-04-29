/**
 * Leetcode 670.最大交换
 * 给定一个非负整数，你至多可以交换一次数字中的任意两位。返回你能得到的最大值。
 * 
 * 示例 1 :
 *  输入: 2736
 *  输出: 7236
 *  解释: 交换数字2和数字7。
 * 
 * 示例 2 :
 *  输入: 9973
 *  输出: 9973
 *  解释: 不需要交换。
 * 
 * 注意: 给定数字的范围是 [0, 10^8]
 */
#include <vector>
#include <algorithm>
using namespace std;

/**
 * 思路:
 * 1.先把数字转化为数组
 * 2.统计各个数字最后出现的位置, 记为last数组
 * 3.从左向右遍历, 根据贪心, 如果之后有较大的数字, 用其中最大的数字交换;
 *   如果有多个最大的数字, 用最后遇到的那一个交换
 */
class Solution {
public:
    int maximumSwap(int num) {
        vector<int> v;
        int tmp = num;
        /* 转化为数组形式 */
        while (tmp) {
            v.push_back(tmp % 10);
            tmp /= 10;
        }
        int n = v.size();
        if (n < 2) return num;
        /* 先翻转
         * PS:为了便于理解翻转了数组, 也可以不翻转节省时间
         * 只不过需要:
         *  (1)初始化last全部为INT_MAX
         *  (2)下面的外层循环i从n-1开始倒着遍历
         *  (3)last[j] > i */
        reverse(v.begin(), v.end());
        /* 统计各个数字最后出现的位置 */
        int last[10];
        for (int i = 0; i < n; i++) {
            last[v[i]] = i;
        }
        /* 从左向右扫描数字 */
        for (int i = 0; i < n; i++) {
            /* 找到在数字v[i]右边比它大的数字的最大值
             * 所以要从9倒着找 */
            for (int j = 9; j > v[i]; j--) {
                if (last[j] > i) {
                    /* 只允许交换一次, 直接退出循环 */
                    swap(v[i], v[last[j]]);
                    goto out;
                }
            }
        }
    out:
        int res = 0;
        for (int i = 0; i < n; i++) {
            res *= 10;
            res += v[i];
        }
        return res;
    }
};