/* Leectode 238.除自身以外数组的乘积
 * 给你一个长度为 n 的整数数组 nums，其中 n > 1，返回输出数组 output ，
 * 其中 output[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积。
 * 示例:
 *  输入: [1,2,3,4]
 *  输出: [24,12,8,6]
 * 说明: 
 *  (1)请不要使用除法
 *  (2)在 O(n) 时间复杂度内完成此题。
 *  (3)在常数空间复杂度内完成这个题目(出于对空间复杂度分析的目的，输出数组不被视为额外空间)
 */
#include <vector>
using namespace std;

/* output[i] = i左边的乘积 x i右边的乘积 */
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int size = nums.size();
        vector<int> output(size);
        int n = 1; /* n为i左边边的乘积 */
        for (int i = 0; i < size; i++) {
            output[i] = n;
            n *= nums[i];
        }
        /* 第一次循环后, output[i]存放i左边的乘积 */

        n = 1; /* n为i右边的乘积 */
        for (int i = size-1; i >= 0; i--) {
            output[i] *= n;
            n *= nums[i];
        }
        return output;
    }
};