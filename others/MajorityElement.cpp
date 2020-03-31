/* Leetcode 168.多数元素
 * 给定一个大小为n的数组, 找到其中的多数元素. 多数元素是指在数组中出现次数大于⌊n/2⌋的元素.
 * 你可以假设数组是非空的, 并且给定的数组总是存在多数元素.
 */
#include <vector>
using namespace std;

//摩尔投票法找众数
//在遍历过的数字中, 设出现次数最多的数字为x, 那么当计数器归零时, 相同数量的x和其他数相互抵消
//我们通过忽略之前遍历过的数字, 使得整个数组的众数在剩下的数字中仍然是众数
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int cnt = 1;
        int val = nums[0]; //众数
        for (int i = 1; i < nums.size(); i++) {
            if (val == nums[i])
                cnt++;
            else
                cnt--;
            if (!cnt) {
                val = nums[i];
                cnt = 1;
            }
        }
        return val;
    }
};