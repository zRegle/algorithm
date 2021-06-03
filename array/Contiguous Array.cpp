/**
 * Leetcode 525. 连续数组
 * 给定一个二进制数组 nums , 找到含有相同数量的 0 和 1 的最长连续子数组，并返回该子数组的长度。
 *  
 * 示例 1:
 *  输入: nums = [0,1]
 *  输出: 2
 *  说明: [0, 1] 是具有相同数量0和1的最长连续子数组。
 * 示例 2:
 *  输入: nums = [0,1,0]
 *  输出: 2
 *  说明: [0, 1] (或 [1, 0]) 是具有相同数量0和1的最长连续子数组。
 *  
 * 提示：
 * (1)1 <= nums.length <= 10^5
 * (2)nums[i] 不是 0 就是 1
 */
#include <unordered_map>
#include <vector>
using std::vector;
using std::unordered_map;
using std::max;

/**
 * 与560类似, 也是利用前缀和求解
 * 
 * 我们设置一个counter, 遇到0减一, 遇到1加一
 * 如果counter在到达i和j时相等, 那么[i+1, j]之间的0和1个数相等
 */

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return 0;
        /**
         * key -> counter数值
         * value -> 该counter第一次出现的位置
         *          (确保长度最长)
         */
        unordered_map<int, int> map;
        map[0] = -1;
        int counter = 0, ans = 0, prev;
        for (int i = 0; i < n; i++) {
            nums[i] == 0 ? counter-- : counter++;
            if (map.count(counter) != 0) {
                prev = map[counter];
                ans = max(ans, i - prev);
            } else {
                map[counter] = i;
            }
        }
        return ans;
    }
};