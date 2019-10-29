/* Leetcode 41.缺失的第一个正数
 * 给定一个未排序的整数数组,找出其中没有出现的最小的正整数。
 * 你的算法的时间复杂度应为O(n),并且只能使用常数级别的空间。
 * 示例 1:
 *  输入: [1,2,0]
 *  输出: 3
 * 示例 2:
 *  输入: [3,4,-1,1]
 *  输出: 2
 * 示例 3:
 *  输入: [7,8,9,11,12]
 *  输出: 1
 */
#include <vector>
using namespace std;

/* 假设数组A,大小是n
 * 1.缺失的正数不可能大于n+1
 *      假设缺失的数是n+2, 那么表明[1,n+1]的数都在数组A里
 *      但是A的大小为n, 所以不可能
 * 2.不用管0和负数
 * 3.假设数字a在区间[1,n]里, 我们将数字a放在A[a-1]的位置上
 * 4.第一个不在对应位置上的数字即是我们要的结果
 */
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int size = nums.size();
        for (int i = 0; i < size; i ++)
            //虽然这里用了while, 但是时间复杂度仍然为O(n)
            //因为当我们"放置"好一个数后, 这个数就不会再变了
            //每次我们放置好一个数, 最多需要操作n次, 所以为O(n)
            while (nums[i] > 0 && nums[i] <= size && nums[i] != nums[nums[i]-1])
                swap(nums[i], nums[nums[i]-1]);
        for (int i = 0; i < size; i++)
            if (nums[i] != i+1)
                return i+1;
        return size+1;
    }
};