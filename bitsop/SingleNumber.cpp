/* Leetcode 136.只出现一次的数字
 * 给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
 * 说明：你的算法时间复杂度应为O(n), 空间复杂度应为O(1)
 * 示例 1:
 *  输入: [2,2,1]
 *  输出: 1
 * 示例 2:
 *  输入: [4,1,2,1,2]
 *  输出: 4
 */
#include <vector>
using namespace std;

//异或运算:
//异或满足交换律和结合律
//a^b^c = a^c^b = b^a^c = b^c^a = c^a^b = c^b^a
//假设i是只出现一次的数, 那么根据满足交换律和结合律
//所以A[0..i-1]相互异或的结果 = A[i+1..n]相互异或的结果, 记为a
//又因为 a^i^a = i, 所以A[0..n]相互异或的结果即为答案
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ans = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            ans ^= nums[i];
        }
        return ans;
    }
};