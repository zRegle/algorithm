/* Leetcode 152.最大子序列乘积
 * 给定一个整数数组nums, 找出一个序列中乘积最大的连续子序列(该序列至少包含一个数)
 */
#include <vector>
#include <climits>
using namespace std;

//需要考虑到偶数个负数相乘得到正数的情况
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];
        int max_pos, min_neg, product;
        //max_pos当前的非负数乘积, min_neg当前的非正数乘积
        max_pos = min_neg = 0;
        product = INT_MIN;
        for (int n : nums) {
            if (!n) { //n == 0时, reset
                max_pos = min_neg = 0;
            } else if (n > 0) {
                //n为正数时, max_pos有可能为0, 所以要用max()
                max_pos = max(max_pos * n , n);
                min_neg *= n; //min_neg乘以一个正数, 肯定不比原来的大
            } else { //n为负数
                int tmp = max_pos;
                //非正数min_neg乘以n, 肯定不比非负数max_pos乘以n小
                max_pos = min_neg * n;
                //更新min_neg, min_neg可能为0, 所以要用min
                min_neg = min(tmp * n, n);
            }
            product = max(max_pos, product);
        }
        return product;
    }
};